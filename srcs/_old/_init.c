/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 21:13:34 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/29 13:56:39 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_img(void *mlx, t_img *img, int width, int height)
{
	img->img = mlx_new_image(mlx, width, height);
	if (!img->img)
		return (ft_error("mlx_new_image: Failed"));
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
	return (0);
}

int	init_window(t_data *data)
{
	data->graphic.mlx = mlx_init();
	if (!data->graphic.mlx)
		return (ft_error("mlx_init: Failed"));
	data->graphic.win = mlx_new_window(data->graphic.mlx,
			data->graphic.win_width, data->graphic.win_height, "cub3D");
	if (!data->graphic.win)
		return (ft_error("mlx_new_window: Failed"));
	// if (init_img(data->graphic.mlx, &data->graphic.mini_map,
	// 		data->graphic.win_width * MINIMAP_SCALE_FACTOR, data->graphic.win_height * MINIMAP_SCALE_FACTOR))
	// 	return (1);
	if (init_img(data->graphic.mlx, &data->graphic.game,
			data->graphic.win_width, data->graphic.win_height))
		return (1);
	return (0);
}
