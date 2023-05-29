/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 13:23:02 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/29 17:24:42 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	has_wall_at(t_data *data, float new_x, float new_y)
// {
// 	if (new_x < 0 || new_x > data->graphic.win_width
// 		|| new_y < 0 || new_y > data->graphic.win_height)
// 		return (1);
// 	if (data->map.map[(int)floor(new_y / TILE_SIZE)]
// 		[(int)floor(new_x / TILE_SIZE)] != '0')
// 		return (1);
// 	return (0);
// }

void	render_player(t_data *data)
{
	draw_circle(&data->graphic.mini_map, &data->player.coord,
		RADIUS, mlx_get_color_value(data->graphic.mlx, 0xFF0000));
}

void	render_minimap(t_data *data)
{
	int		x;
	int		y;
	t_point	start;
	t_point	end;

	y = -1;
	while (data->map.map[++y])
	{
		x = -1;
		while (data->map.map[y][++x])
		{
			start = create_point((x * TILE_SIZE * MINIMAP_SCALE_FACTOR),
					(y * TILE_SIZE * MINIMAP_SCALE_FACTOR));
			end = create_point((x + 1) * TILE_SIZE * MINIMAP_SCALE_FACTOR,
					(y + 1) * TILE_SIZE * MINIMAP_SCALE_FACTOR);
			if (ft_strchr("0NSWE", data->map.map[y][x]))
				draw_rect_mini(&data->graphic.mini_map, &start, &end,
					mlx_get_color_value(data->graphic.mlx, 0xFFFFFF));
			else if (ft_strchr("1", data->map.map[y][x]))
				draw_rect_mini(&data->graphic.mini_map, &start, &end,
					mlx_get_color_value(data->graphic.mlx, 0x202020));
		}
	}
}
