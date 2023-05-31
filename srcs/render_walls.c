/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 00:48:54 by abrisse           #+#    #+#             */
/*   Updated: 2023/06/01 00:49:45 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_img	get_texture_to_render(t_ray *ray, t_data *data)
{
	if (ray->was_hit_horizontal)
	{
		if (ray->is_facing_up)
			return (data->graphic.north_texture);
		else
			return (data->graphic.south_texture);
	}
	else
	{
		if (ray->is_facing_left)
			return (data->graphic.west_texture);
		else
			return (data->graphic.east_texture);
	}
}

static t_to_draw	get_texture_data(t_data *data, int x)
{
	t_to_draw	texture_data;

	texture_data.x = x * WALL_STRIP_WIDTH;
	texture_data.y = (data->graphic.win_height / 2)
		- (data->rays[x].strip.height / 2);
	if (texture_data.y < 0)
		texture_data.y = 0;
	texture_data.width = WALL_STRIP_WIDTH;
	texture_data.height = data->graphic.win_height / 2
		+ data->rays[x].strip.height / 2;
	if (texture_data.height > data->graphic.win_height)
		texture_data.height = data->graphic.win_height;
	return (texture_data);
}

static int	get_pixel_color(t_img texture, t_ray *ray, t_data *data, int y)
{
	int	color_x;
	int	color_y;
	int	color;
	int	top_distance;

	if (ray->was_hit_horizontal)
		color_x = (int)ray->hit_coord.x % TILE_SIZE;
	else
		color_x = (int)ray->hit_coord.y % TILE_SIZE;
	top_distance = y + (int)(ray->strip.height / 2)
		- (data->graphic.win_height / 2);
	color_y = top_distance * (float)TILE_SIZE / (int)ray->strip.height;
	color = texture.addr[color_y * texture.line_len + color_x];
	return (color);
}

void	render_walls(t_data *data)
{
	int			x;
	int			y;
	int			pos_x;
	t_to_draw	texture_data;
	t_img		texture_to_render;

	x = -1;
	while (++x < data->num_rays)
	{
		data->rays[x].wall_distance = data->rays[x].hit_distance
			* cos(data->rays[x].angle - data->player.angle);
		data->rays[x].strip.height = (TILE_SIZE / data->rays[x].wall_distance)
			* data->distance_projection;
		texture_data = get_texture_data(data, x);
		texture_to_render = get_texture_to_render(&data->rays[x], data);
		y = texture_data.y - 1;
		while (++y < texture_data.height)
		{
			pos_x = data->graphic.win_width - x - 1;
			texture_data.color = get_pixel_color(texture_to_render,
				&data->rays[x], data, y);
			my_mlx_pixel_put(&data->graphic.game, pos_x, y, texture_data.color);
		}
	}
}
