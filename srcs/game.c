/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 23:10:12 by abrisse           #+#    #+#             */
/*   Updated: 2023/06/11 13:12:27 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	has_wall_at(t_data *data, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = (int)floor(x / TILE_SIZE);
	map_y = (int)floor(y / TILE_SIZE);
	if (map_x < 0 || map_x > data->map.width
		|| map_y < 0 || map_y > data->map.height)
		return (1);
	if (data->map.map[map_y][map_x] == '1')
		return (1);
	return (0);
}

int	what_next(t_data *data)
{
	update_player(data);
	cast_all_rays(data);
	render_background(data);
	render_walls(data);
	if (data->display_mini_map)
	{
		render_minimap(data);
		render_player(data);
	}
	mlx_put_image_to_window(data->graph.mlx, data->graph.win,
		data->graph.game.img, 0, 0);
	return (0);
}

void	start(t_data *data)
{
	mlx_loop_hook(data->graph.mlx, what_next, data);
	mlx_hook(data->graph.win, 17, 1L << 0, cross_pressed, data);
	mlx_hook(data->graph.win, 2, 1L << 0, key_pressed, data);
	mlx_hook(data->graph.win, 3, 1L << 1, key_released, data);
	mlx_loop(data->graph.mlx);
}
