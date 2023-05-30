/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 23:10:12 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/31 00:31:56 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* fonction validée (potentiel source d'erreur tout de même) */
int	has_wall_at(t_data *data, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = (int)floor(x / TILE_SIZE);
	map_y = (int)floor(y / TILE_SIZE);
	if (map_x < 0 || map_x > data->map.width
		|| map_y < 0 || map_y > data->map.height)
		return (1);
	return (data->map.map[map_y][map_x] == '1');
}

int	what_next(t_data *data)
{
	update_player(data);
	cast_all_rays(data);
	render_background(data);
	render_walls(data);
	render_minimap(data);

	render_player(data);
	mlx_put_image_to_window(data->graphic.mlx, data->graphic.win,
		data->graphic.game.img, 0, 0);
	if (data->display_mini_map)
	{
		mlx_put_image_to_window(data->graphic.mlx, data->graphic.win,
			data->graphic.mini_map.img, 0, 0);
	}
//	usleep(5000);
	return (0);
}

/* fonction validée */
void	start(t_data *data)
{
	mlx_loop_hook(data->graphic.mlx, what_next, data);
	mlx_hook(data->graphic.win, 17, 1L << 0, cross_pressed, data);
	mlx_hook(data->graphic.win, 2, 1L << 0, key_pressed, data);
	mlx_hook(data->graphic.win, 3, 1L << 1, key_released, data);
	mlx_loop(data->graphic.mlx);
}
