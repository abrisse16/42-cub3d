/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 21:13:34 by abrisse           #+#    #+#             */
/*   Updated: 2023/06/01 18:45:58 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_data *data)
{
	init_player(data);
	data->map.map[(int)data->player.coord.y / TILE_SIZE]
	[(int)data->player.coord.x / TILE_SIZE] = '0';
	data->fov_angle = FOV_ANGLE * (M_PI / 180);
	data->distance_projection = (data->graphic.win_width / 2)
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
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len, &img->endian);
	return (0);
}

static int	init_texutres(t_data *data)
{
	if (get_texture(data->graphic.mlx, data->no, &data->graphic.north_texture)
		|| get_texture(data->graphic.mlx, data->so, &data->graphic.south_texture)
		|| get_texture(data->graphic.mlx, data->we, &data->graphic.west_texture)
		|| get_texture(data->graphic.mlx, data->ea, &data->graphic.east_texture))
		return (1);
	return (0);
}

int	init_graphic(t_data *data)
{
	data->graphic.mlx = mlx_init();
	if (!data->graphic.mlx)
		return (ft_error("mlx_init: Failed"));
	mlx_get_screen_size(data->graphic.mlx, &data->graphic.win_width,
		&data->graphic.win_height);
	data->graphic.win_width = data->graphic.win_width * 0.8;
	data->graphic.win_height = data->graphic.win_height * 0.8;
	data->num_rays = data->graphic.win_width / WALL_STRIP_WIDTH;
	data->rays = ft_malloc(sizeof(t_ray) * data->num_rays);
	if (!data->rays)
		return (ft_perror("malloc"));
	if (init_texutres(data))
		return (1);
	data->graphic.win = mlx_new_window(data->graphic.mlx,
			data->graphic.win_width, data->graphic.win_height, "cub3D");
	if (!data->graphic.win)
		return (ft_error("mlx_new_window: Failed"));
	if (init_img(data->graphic.mlx, &data->graphic.game,
			data->graphic.win_width, data->graphic.win_height))
		return (1);
	return (0);
}
