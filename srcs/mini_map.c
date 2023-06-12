/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:13:45 by abrisse           #+#    #+#             */
/*   Updated: 2023/06/12 22:20:36 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float	render_minimap_background(t_data *data)
{
	t_to_draw	to_draw;
	float		fact;

	to_draw.x = 0;
	to_draw.y = 0;
	fact = 1;
	to_draw.width = data->map.width * TILE_SIZE * MINIMAP_SCALE_FACTOR * fact;
	to_draw.height = data->map.height * TILE_SIZE * MINIMAP_SCALE_FACTOR * fact;
	while (to_draw.width > data->graph.win_width / 2
		|| to_draw.height > data->graph.win_height / 2)
	{
		fact -= 0.05;
		to_draw.width = data->map.width * TILE_SIZE * MINIMAP_SCALE_FACTOR
			* fact;
		to_draw.height = data->map.height * TILE_SIZE * MINIMAP_SCALE_FACTOR
			* fact;
	}
	to_draw.color = 0x202020;
	draw_color_rect(&data->graph.game, &to_draw);
	return (fact);
}

void	render_minimap(t_data *data)
{
	int			x;
	int			y;
	t_to_draw	to_draw;
	float		fact;

	fact = render_minimap_background(data);
	data->fact = fact;
	to_draw.width = TILE_SIZE * MINIMAP_SCALE_FACTOR * fact + 1;
	to_draw.height = TILE_SIZE * MINIMAP_SCALE_FACTOR * fact + 1;
	y = -1;
	while (data->map.map[++y])
	{
		x = -1;
		while (data->map.map[y][++x])
		{
			to_draw.x = x * TILE_SIZE * MINIMAP_SCALE_FACTOR * fact;
			to_draw.y = y * TILE_SIZE * MINIMAP_SCALE_FACTOR * fact;
			if (ft_strchr("0NSWE", data->map.map[y][x]))
			{
				to_draw.color = 0xFFFFFF;
				draw_color_rect(&data->graph.game, &to_draw);
			}
		}
	}
}
