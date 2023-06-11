/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 00:48:54 by abrisse           #+#    #+#             */
/*   Updated: 2023/06/11 16:01:31 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_img	get_texture_to_render(t_ray *ray, t_data *data)
{
	if (ray->was_hit_horizontal)
	{
		if (ray->is_facing_up)
			return (data->graph.north_texture);
		else
			return (data->graph.south_texture);
	}
	else
	{
		if (ray->is_facing_left)
			return (data->graph.west_texture);
		else
			return (data->graph.east_texture);
	}
}

static t_texture_data	get_texture_data(t_data *data, int x)
{
	t_texture_data	texture_data;

	texture_data.offset_x = x * WALL_STRIP_WIDTH;
	texture_data.offset_y = (data->graph.win_height / 2)
		- ((int)data->rays[x].projected_height / 2);
	if (texture_data.offset_y < 0)
		texture_data.offset_y = 0;
	texture_data.width = WALL_STRIP_WIDTH;
	texture_data.height = (data->graph.win_height / 2)
		+ ((int)data->rays[x].projected_height / 2);
	if (texture_data.height > data->graph.win_height)
		texture_data.height = data->graph.win_height;
	return (texture_data);
}

void	render_walls(t_data *data)
{
	int				x;
	int				y;
	t_texture_data	texture_data;
	t_img			texture_to_render;
	int				color;

	x = -1;
	while (++x < data->num_rays)
	{
		data->rays[x].wall_distance = data->rays[x].hit_distance
			* cos(data->rays[x].angle - data->player.angle);
		data->rays[x].projected_height = (TILE_SIZE
				/ data->rays[x].wall_distance) * data->distance_projection;
		texture_data = get_texture_data(data, x);
		texture_to_render = get_texture_to_render(&data->rays[x], data);
		get_color_x(&data->rays[x], &texture_data, texture_to_render);
		y = texture_data.offset_y - 1;
		while (++y < texture_data.height)
		{
			data->rays[x].y = y;
			get_color_y(&data->rays[x], data, &texture_data, texture_to_render);
			color = get_color(&texture_data, texture_to_render);
			my_mlx_pixel_put(&data->graph.game, x, y, color);
		}
	}
}
