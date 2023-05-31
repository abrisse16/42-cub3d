/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 13:23:02 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/31 13:24:57 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_background(t_data *data)
{
	data->to_draw.x = 0;
	data->to_draw.width = data->graphic.win_width;
	data->to_draw.height = data->graphic.win_height / 2;
	data->to_draw.y = 0;
	data->to_draw.color = data->celling[0] << 16 | data->celling[1] << 8
		| data->celling[2];
	draw_color_rect(&data->graphic.game, &data->to_draw);
	data->to_draw.y = data->graphic.win_height / 2;
	data->to_draw.color = data->floor[0] << 16 | data->floor[1] << 8
		| data->floor[2];
	draw_color_rect(&data->graphic.game, &data->to_draw);
}

static void	render_wall(t_ray *ray, t_data *data)
{
	if (ray->was_hit_horizontal)
	{
		if (ray->is_facing_up)
			ray->strip.color = 0x00FF00;
		else
			ray->strip.color = 0x0000FF;
	}
	else
	{
		if (ray->is_facing_left)
			ray->strip.color = 0xFF0000;
		else
			ray->strip.color = 0xFFFF00;
	}
	draw_color_rect(&data->graphic.game, &ray->strip);
}

void	render_walls(t_data *data)
{
	int	x;

	x = -1;
	while (++x < data->num_rays)
	{
		data->rays[x].wall_distance = data->rays[x].hit_distance
			* cos(data->rays[x].angle - data->player.angle);
		data->rays[x].strip.height = (TILE_SIZE / data->rays[x].wall_distance)
			* data->distance_projection;
		if (data->rays[x].strip.height > data->graphic.win_height)
			data->rays[x].strip.height = data->graphic.win_height;
		data->rays[x].strip.y = (data->graphic.win_height / 2)
			- (data->rays[x].strip.height / 2);
		if (data->rays[x].strip.y < 0)
			data->rays[x].strip.y = 0;
		data->rays[x].strip.width = WALL_STRIP_WIDTH;
		data->rays[x].strip.x = data->graphic.win_width - 1 - x
			* WALL_STRIP_WIDTH;
		render_wall(&data->rays[x], data);
	}
}

void	render_player(t_data *data)
{
	int	x;

	x = -1;
	while (++x < data->num_rays)
		if (x % (TILE_SIZE / 2) == 0)
			draw_ray(&data->graphic.game, &data->player.coord,
				data->rays[x].angle, data->rays[x].hit_distance + 1);
	draw_circle(&data->graphic.game, &data->player.coord,
		RADIUS, 0xFF0000);
}
