/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 19:14:21 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/30 21:04:35 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* fonction validée */
/* à noter : pas de rotation quand on est contre un mur */
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
		move_x = (cos(data->player.angle) * data->player.walk_direction * data->player.walk_speed)
			+ (cos(data->player.angle + M_PI_2) * data->player.side_direction * data->player.walk_speed);
		move_y = - (sin(data->player.angle) * data->player.walk_direction * data->player.walk_speed)
			- (sin(data->player.angle + M_PI_2) * data->player.side_direction * data->player.walk_speed);
		move_x += data->player.coord.x;
		move_y += data->player.coord.y;
		if (!has_wall_at(data, move_x, move_y))
		{
			data->player.coord.x = move_x;
			data->player.coord.y = move_y;
		}
	}
//	float	new_x;
//	float	new_y;
//	int		distance_walk;
//	int		distance_side;

//	data->player.angle += data->player.turn_direction
//		* data->player.turn_speed;
//	distance_walk = data->player.walk_direction * data->player.walk_speed;
//	new_x = data->player.coord.x + cos(data->player.angle)
//		* distance_walk;
//	new_y = data->player.coord.y - sin(data->player.angle)
//		* distance_walk;
//	if (has_wall_at(data, new_x, new_y))
//		return ;
//	data->player.coord.x = new_x;
//	data->player.coord.y = new_y;
//	distance_side = data->player.side_direction * data->player.walk_speed;
//	new_x = data->player.coord.x + cos(data->player.angle + M_PI_2)
//		* distance_side;
//	new_y = data->player.coord.y - sin(data->player.angle + M_PI_2)
//		* distance_side;
//	if (has_wall_at(data, new_x, new_y))
//		return ;
//	data->player.coord.x = new_x;
//	data->player.coord.y = new_y;
}
