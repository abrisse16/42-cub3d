/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 21:13:34 by abrisse           #+#    #+#             */
/*   Updated: 2023/06/13 21:01:42 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_data *data)
{
	init_player(data);
	data->map.map[(int)data->player.coord.y / TILE_SIZE]
	[(int)data->player.coord.x / TILE_SIZE] = '0';
	data->fov_angle = FOV_ANGLE * (M_PI / 180);
	data->distance_projection = (data->graph.win_width / 2)
		/ tan(data->fov_angle / 2);
	data->display_mini_map = 0;
}

int	init_img(void *mlx, t_img *img, int width, int height)
{
	img->img = mlx_new_image(mlx, width, height);
	if (!img->img)
		return (ft_error("mlx_new_image: Failed"));
	img->width = width;
	img->height = height;
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
	return (0);
}

static int	get_texture(void *mlx, char *path, t_img *img)
{
	t_texture_data	texture_data;
	t_img			tmp;
	int				x;
	int				y;

	if (init_img(mlx, img, TILE_SIZE, TILE_SIZE))
		return (1);
	tmp.img = mlx_xpm_file_to_image(mlx, path, &tmp.width, &tmp.height);
	if (!tmp.img)
		return (ft_error("mlx_xpm_file_to_image: Failed"));
	tmp.addr = mlx_get_data_addr(tmp.img, &tmp.bpp, &tmp.line_len,
			&tmp.endian);
	y = -1;
	while (++y < TILE_SIZE)
	{
		x = -1;
		while (++x < TILE_SIZE)
		{
			texture_data.color_x = x * ((float)tmp.width / TILE_SIZE);
			texture_data.color_y = y * ((float)tmp.height / TILE_SIZE);
			my_mlx_pixel_put(img, x, y, get_color(&texture_data, tmp));
		}
	}
	mlx_destroy_image(mlx, tmp.img);
	return (0);
}

static int	init_texutres(t_data *data)
{
	if (get_texture(data->graph.mlx, data->no, &data->graph.north_texture)
		|| get_texture(data->graph.mlx, data->so, &data->graph.south_texture)
		|| get_texture(data->graph.mlx, data->we, &data->graph.west_texture)
		|| get_texture(data->graph.mlx, data->ea, &data->graph.east_texture))
		return (1);
	return (0);
}

int	init_graph(t_data *data)
{
	data->graph.mlx = mlx_init();
	if (!data->graph.mlx)
		return (ft_error("mlx_init: Failed"));
	mlx_get_screen_size(data->graph.mlx, &data->graph.win_width,
		&data->graph.win_height);
	data->graph.win_width = data->graph.win_width * WIN_SCALE_FACTOR;
	data->graph.win_height = data->graph.win_height * WIN_SCALE_FACTOR;
	data->num_rays = data->graph.win_width / WALL_STRIP_WIDTH;
	data->rays = ft_malloc(sizeof(t_ray) * data->num_rays);
	if (!data->rays)
		return (ft_perror("malloc"));
	if (init_texutres(data))
		return (1);
	data->graph.win = mlx_new_window(data->graph.mlx,
			data->graph.win_width, data->graph.win_height, "cub3D");
	if (!data->graph.win)
		return (ft_error("mlx_new_window: Failed"));
	if (init_img(data->graph.mlx, &data->graph.game,
			data->graph.win_width, data->graph.win_height))
		return (1);
	return (0);
}
