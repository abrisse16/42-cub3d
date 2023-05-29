/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:14:40 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/30 00:37:37 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_wall_dimension(t_data *data, int x)
{
	data->wall.wall_distance = data->rays[x].hit_distance
		* cos(data->rays[x].angle - data->player.rotation_angle);
	data->wall.projected_wall_height = (TILE_SIZE / data->wall.wall_distance)
		* data->graphic.distance_projection;
}

static void	get_strip_dimension(t_data *data, int x)
{
	data->to_draw.y = (data->graphic.win_height / 2)
		- (data->wall.projected_wall_height / 2);
	if (data->to_draw.y < 0)
		data->to_draw.y = 0;
	data->to_draw.x = x * WALL_STRIP_WIDTH;
	data->to_draw.width = WALL_STRIP_WIDTH;
	data->to_draw.height = (data->graphic.win_height / 2)
		+ (data->wall.projected_wall_height / 2);
	if (data->to_draw.height > data->graphic.win_height)
		data->to_draw.height = data->graphic.win_height;
}

t_img	get_wall_texture(t_data *data, int x)
{
	if (data->rays[x].was_hit_horizontal)
	{
		if (data->rays[x].is_facing_up)
			return (data->graphic.north_texture);
		return (data->graphic.south_texture);
	}
	else
	{
		if (data->rays[x].is_facing_left)
			return (data->graphic.west_texture);
		return (data->graphic.east_texture);
	}
}

void	get_coord_texture(t_data *data, int x, int y)
{
	if (data->rays[x].was_hit_horizontal)
		data->wall.color_x = (int)data->rays[x].hit_coord.x % TILE_SIZE;
	else
		data->wall.color_x = (int)data->rays[x].hit_coord.y % TILE_SIZE;
	data->wall.top_distance = y + ((int)data->wall.projected_wall_height / 2)
		- (data->graphic.win_height / 2);
	data->wall.color_y = data->wall.top_distance * ((float)TILE_SIZE
			/ (int)data->wall.projected_wall_height);
}

int	get_color(t_img img, int x, int y)
{
	return (*(img.addr + (x + y * img.line_len)));
}

void	render_walls(t_data *data)
{
	int	x;
//	int	y;
	t_img wall_img;

	x = -1;
	while (++x < data->num_rays)
	{
		get_wall_dimension(data, x);
		get_strip_dimension(data, x);
		
		
		if (data->rays[x].was_hit_horizontal)
		{
			if (data->rays[x].is_facing_up)
				data->to_draw.color = 0x00FF00;
			else
				data->to_draw.color = 0x0000FF;
		}
		else
		{
			if (data->rays[x].is_facing_left)
				data->to_draw.color = 0xFF0000;
			else
				data->to_draw.color = 0xFFFF00;
		}
		draw_rect(&data->graphic.game, &data->to_draw);
		
		
//		wall_img = get_wall_texture(data, x);
//		y = data->to_draw.y - 1;
//		while (++y < data->to_draw.height)
//		{
//			get_coord_texture(data, x, y);
//			my_mlx_pixel_put(data->graphic.game.img, x, y, 0x00FF00);
//				get_color(wall_img, data->wall.color_x, data->wall.color_y));
//		}
	}
	(void)wall_img;
}

void	render_background(t_data *data)
{
	data->to_draw.color = data->celling[0] << 16 | data->celling[1] << 8 | data->celling[2];
	data->to_draw.x = 0;
	data->to_draw.y = 0;
	data->to_draw.width = data->graphic.win_width;
	data->to_draw.height = data->graphic.win_height / 2;
	draw_rect(&data->graphic.game, &data->to_draw);
	data->to_draw.color = data->floor[0] << 16 | data->floor[1] << 8 | data->floor[2];
	data->to_draw.x = 0;
	data->to_draw.y = data->graphic.win_height / 2;
	data->to_draw.width = data->graphic.win_width;
	data->to_draw.height = data->graphic.win_height / 2;
	draw_rect(&data->graphic.game, &data->to_draw);
}