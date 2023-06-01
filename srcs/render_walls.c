/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 00:48:54 by abrisse           #+#    #+#             */
/*   Updated: 2023/06/01 18:52:27 by abrisse          ###   ########.fr       */
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

static t_texture_data	get_texture_data(t_data *data, int x)
{
	t_texture_data	texture_data;

	texture_data.offset_x = x * WALL_STRIP_WIDTH;
	texture_data.offset_y = (data->graphic.win_height / 2)
		- ((int)data->rays[x].projected_height / 2);
	if (texture_data.offset_y < 0)
		texture_data.offset_y = 0;
	texture_data.width = WALL_STRIP_WIDTH;
	texture_data.height = (data->graphic.win_height / 2)
		+ ((int)data->rays[x].projected_height / 2);
	if (texture_data.height > data->graphic.win_height)
		texture_data.height = data->graphic.win_height;
	return (texture_data);
}

static void	get_color(t_ray *ray, t_texture_data *texture_data, t_data *data, int y)
{
	int				distance_from_top;
	
	if (ray->was_hit_horizontal)
		texture_data->color_x = (int)ray->hit_coord.x % TILE_SIZE;
	else
		texture_data->color_x = (int)ray->hit_coord.y % TILE_SIZE;
	distance_from_top = y + ((int)ray->projected_height / 2) - (data->graphic.win_height / 2);
	texture_data->color_y = distance_from_top * ((float)TILE_SIZE / (int)ray->projected_height);
}

void	render_walls(t_data *data)
{
	int				x;
	int				y;
	t_texture_data	texture_data;
	t_img			texture_to_render;
	int		color;

	x = -1;
	while (++x < data->num_rays)
	{
		data->rays[x].wall_distance = data->rays[x].hit_distance
			* cos(data->rays[x].angle - data->player.angle);
		data->rays[x].projected_height = (TILE_SIZE / data->rays[x].wall_distance)
			* data->distance_projection;
		texture_data = get_texture_data(data, x);
		texture_to_render = get_texture_to_render(&data->rays[x], data);
		y = texture_data.offset_y - 1;
		while (++y < texture_data.height)
		{
	//		pos_x = data->graphic.win_width - x - 1;
			get_color(&data->rays[x], &texture_data, data, y);
			color = *(texture_to_render.addr + (texture_data.color_x + texture_data.color_y * texture_to_render.line_len));	
			my_mlx_pixel_put(&data->graphic.game, x, y, color);
		}
	}
}
