/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 23:10:12 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/29 22:34:12 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	normalize_angle(float angle)
{
	angle = remainder(angle, 2 * M_PI);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}

int	has_wall_at(t_data *data, float x, float y)
{
	int map_x;
	int map_y;

	map_x = (int)floor(x / TILE_SIZE);
	map_y = (int)floor(y / TILE_SIZE);
	if (x < 0 || x > data->graphic.win_width || y < 0 || y > data->graphic.win_height)
		return (1);
	return (data->map.map[map_y][map_x] == '1');
}

static void	update_player(t_data *data)
{
	float	move_x;
	float	move_y;
	
	if (data->player.turn_direction != 0)
	{
		data->player.rotation_angle += data->player.turn_direction
			* data->player.turn_speed;
		data->player.rotation_angle = normalize_angle(data->player.rotation_angle);
	}
	if (data->player.walk_direction != 0 || data->player.side_direction != 0)
	{
		move_x = (cos(data->player.rotation_angle) * data->player.walk_direction * data->player.walk_speed)
			+ (cos(data->player.rotation_angle + M_PI_2) * data->player.side_direction * data->player.walk_speed);
		move_y = (sin(data->player.rotation_angle) * data->player.walk_direction * data->player.walk_speed)
			+ (sin(data->player.rotation_angle + M_PI_2) * data->player.side_direction * data->player.walk_speed);
		move_x += data->player.coord.x;
		move_y += data->player.coord.y;
		if (!has_wall_at(data, move_x, move_y))
		{
			data->player.coord.x = move_x;
			data->player.coord.y = move_y;
		}
	}
}

static int	what_next(t_data *data)
{
	update_player(data);
	cast_all_rays(data);
	render_background(data);
	render_walls(data);

	mlx_put_image_to_window(data->graphic.mlx, data->graphic.win, data->graphic.game.img, 0, 0);
	return (0);
}

void	start(t_data *data)
{
	mlx_loop_hook(data->graphic.mlx, what_next, data);
	mlx_hook(data->graphic.win, 17, 1L << 0, cross_pressed, data);
	mlx_hook(data->graphic.win, 2, 1L << 0, key_pressed, data);
	mlx_hook(data->graphic.win, 3, 1L << 1, key_released, data);
	mlx_loop(data->graphic.mlx);
}
