/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 13:23:02 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/31 00:34:28 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* fonction validé */
void	render_background(t_data *data)
{
	data->to_draw.x = 0;
	data->to_draw.width = data->graphic.win_width;
	data->to_draw.height = data->graphic.win_height / 2;
	data->to_draw.y = 0;
	data->to_draw.color = data->celling[0] << 16 | data->celling[1] << 8 | data->celling[2];
	draw_color_rect(&data->graphic.game, &data->to_draw);
	data->to_draw.y = data->graphic.win_height / 2;
	data->to_draw.color = data->floor[0] << 16 | data->floor[1] << 8 | data->floor[2];
	draw_color_rect(&data->graphic.game, &data->to_draw);
}

/* fonction validée */
static void	render_minimap_background(t_data *data)
{
	t_to_draw to_draw;

	to_draw.x = 0;
	to_draw.y = 0;
	to_draw.width = data->graphic.win_width * MINIMAP_SCALE_FACTOR;
	to_draw.height = data->graphic.win_height * MINIMAP_SCALE_FACTOR;
	to_draw.color = 0x202020;
	draw_color_rect(&data->graphic.mini_map, &to_draw);
}

/* fonction validéee */
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
				draw_color_rect(&data->graphic.mini_map, &to_draw);
			}
		}
	}
}

/* fonction en cours de dévelopement */
void	render_walls(t_data *data)
{
	int	x;
	
	x = -1;
	while (++x < data->num_rays)
	{
		data->rays[x].wall_distance = data->rays[x].hit_distance * cos(data->rays[x].angle - data->player.angle);
		
		data->rays[x].strip.height = (TILE_SIZE / data->rays[x].wall_distance) * data->graphic.distance_projection;
		data->rays[x].strip.y = (data->graphic.win_height / 2) - (data->rays[x].strip.height / 2);
		if (data->rays[x].strip.y < 0)
			data->rays[x].strip.y = 0;
		data->rays[x].strip.width = WALL_STRIP_WIDTH;
		data->rays[x].strip.x = data->graphic.win_width - 1 - x * WALL_STRIP_WIDTH;
		if (data->rays[x].strip.height > data->graphic.win_height)
			data->rays[x].strip.height = data->graphic.win_height;
		
		if (data->rays[x].was_hit_horizontal)
		{
			if (data->rays[x].is_facing_up)
				data->rays[x].strip.color = 0x00FF00;
			else
				data->rays[x].strip.color = 0x0000FF;
		}
		else
		{
			if (data->rays[x].is_facing_left)
				data->rays[x].strip.color = 0xFF0000;
			else
				data->rays[x].strip.color = 0xFFFF00;
		}
		draw_color_rect(&data->graphic.game, &data->rays[x].strip);
	}
}

void	render_player(t_data *data)
{
	int	x;
	
	x = -1;
	while (++x < data->num_rays)
		if (x % (TILE_SIZE / 2) == 0)
			draw_ray(&data->graphic.mini_map, &data->player.coord, data->rays[x].angle, data->rays[x].hit_distance + 1);
	draw_circle(&data->graphic.mini_map, &data->player.coord,
		RADIUS, 0xFF0000);
}
