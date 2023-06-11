/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 19:14:21 by abrisse           #+#    #+#             */
/*   Updated: 2023/06/11 15:40:09 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_player_rotation(t_data *data)
{
	if (data->map.dir == 'E')
		data->player.angle = 0;
	else if (data->map.dir == 'N')
		data->player.angle = M_PI_2;
	else if (data->map.dir == 'W')
		data->player.angle = M_PI;
	else if (data->map.dir == 'S')
		data->player.angle = 3 * M_PI_2;
}

void	init_player(t_data *data)
{
	data->player.turn_direction = 0;
	data->player.walk_direction = 0;
	data->player.side_direction = 0;
	data->player.turn_speed = TURN_SPEED * (M_PI / 180);
	data->player.walk_speed = WALK_SPEED;
	init_player_rotation(data);
}

static int	check_player_wall(t_data *data, float move_x, float move_y)
{
	if (!has_wall_at(data, 2 * move_x + data->player.coord.x,
			2 * move_y + data->player.coord.y)
		&& !has_wall_at(data, data->player.coord.x,
			2 * move_y + data->player.coord.y)
		&& !has_wall_at(data, 2 * move_x + data->player.coord.x,
			data->player.coord.y))
	{
		return (1);
	}
	return (0);
}

void	update_player(t_data *data)
{
	float	move_x;
	float	move_y;

	if (data->player.turn_direction != 0)
	{
		data->player.angle += data->player.turn_direction
			* data->player.turn_speed;
		data->player.angle = normalize_angle(data->player.angle);
	}
	if (data->player.walk_direction != 0 || data->player.side_direction != 0)
	{
		move_x = (cos(data->player.angle) * data->player.walk_direction
				* data->player.walk_speed) + (cos(data->player.angle + M_PI_2)
				* data->player.side_direction * data->player.walk_speed);
		move_y = - (sin(data->player.angle) * data->player.walk_direction
				* data->player.walk_speed) - (sin(data->player.angle + M_PI_2)
				* data->player.side_direction * data->player.walk_speed);
		if (check_player_wall(data, move_x, move_y))
		{
			data->player.coord.x = move_x + data->player.coord.x;
			data->player.coord.y = move_y + data->player.coord.y;
		}
	}
}
