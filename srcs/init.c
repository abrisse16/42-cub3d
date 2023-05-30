/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 21:13:34 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/30 20:38:49 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* fonction validée */
void	init_data(t_data *data)
{
	init_player(data);
	data->graphic.win_width = TILE_SIZE * data->map.width;
	data->graphic.win_height = TILE_SIZE * data->map.height;
	data->map.map[(int)data->player.coord.y / TILE_SIZE]
			[(int)data->player.coord.x / TILE_SIZE] = '0';
	data->fov_angle = FOV_ANGLE * (M_PI / 180);
	data->graphic.distance_projection = (data->graphic.win_width / 2) / tan(data->fov_angle / 2);
	data->num_rays = data->graphic.win_width / WALL_STRIP_WIDTH;
	data->display_mini_map = 1;
}

/* fonction validée */
int	init_img(void *mlx, t_img *img, int width, int height)
{
	img->img = mlx_new_image(mlx, width, height);
	if (!img->img)
		return (ft_error("mlx_new_image: Failed"));
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
	return (0);
}

int	init_graphic(t_data* data)
{
	data->rays = ft_malloc(sizeof(t_ray) * data->num_rays);
	if (!data->rays)
		return (ft_perror("malloc"));
	data->graphic.mlx = mlx_init();
	if (!data->graphic.mlx)
		return (ft_error("mlx_init: Failed"));

	/* à ajouter : init_textures*/
	
	data->graphic.win = mlx_new_window(data->graphic.mlx,
			data->graphic.win_width, data->graphic.win_height, "cub3D");
	if (!data->graphic.win)
		return (ft_error("mlx_new_window: Failed"));
	if (init_img(data->graphic.mlx, &data->graphic.mini_map,
			data->graphic.win_width * MINIMAP_SCALE_FACTOR,
			data->graphic.win_height * MINIMAP_SCALE_FACTOR))
		return (1);
	if (init_img(data->graphic.mlx, &data->graphic.game,
			data->graphic.win_width, data->graphic.win_height))
		return (1);
	return (0);
}

/* fonction à ajouter : init_texutres */
