/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 13:13:45 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/31 13:14:00 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	render_minimap_background(t_data *data)
{
	t_to_draw	to_draw;

	to_draw.x = 0;
	to_draw.y = 0;
	to_draw.width = data->graphic.win_width * MINIMAP_SCALE_FACTOR;
	to_draw.height = data->graphic.win_height * MINIMAP_SCALE_FACTOR;
	to_draw.color = 0x202020;
	draw_color_rect(&data->graphic.game, &to_draw);
}

void	render_minimap(t_data *data)
{
	int			x;
	int			y;
	t_to_draw	to_draw;

	render_minimap_background(data);
	to_draw.width = TILE_SIZE * MINIMAP_SCALE_FACTOR + 1;
	to_draw.height = TILE_SIZE * MINIMAP_SCALE_FACTOR + 1;
	y = -1;
	while (data->map.map[++y])
	{
		x = -1;
		while (data->map.map[y][++x])
		{
			to_draw.x = x * TILE_SIZE * MINIMAP_SCALE_FACTOR;
			to_draw.y = y * TILE_SIZE * MINIMAP_SCALE_FACTOR;
			if (ft_strchr("0NSWE", data->map.map[y][x]))
			{
				to_draw.color = 0xFFFFFF;
				draw_color_rect(&data->graphic.game, &to_draw);
			}
		}
	}
}
