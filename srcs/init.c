/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 21:13:34 by abrisse           #+#    #+#             */
/*   Updated: 2023/06/11 02:42:51 by abrisse          ###   ########.fr       */
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
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
	return (0);
}

static int	get_texture(void *mlx, char *path, t_img *img)
{
	img->img = mlx_xpm_file_to_image(mlx, path, &img->width, &img->height);
	if (!img->img)
		return (ft_error("mlx_xpm_file_to_image: Failed"));
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
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
	data->graph.win_width = data->graph.win_width * 0.8;
	data->graph.win_height = data->graph.win_height * 0.8;
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
