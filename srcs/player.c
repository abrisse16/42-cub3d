/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 19:14:21 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/29 00:05:47 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_player(t_data *data)
{
	float	new_x;
	float	new_y;
	int		distance_walk;
	int		distance_side;

	data->player.rotation_angle += data->player.turn_direction
		* data->player.turn_speed;
	distance_walk = data->player.walk_direction * data->player.walk_speed;
	new_x = data->player.coord.x + cos(data->player.rotation_angle)
		* distance_walk;
	new_y = data->player.coord.y - sin(data->player.rotation_angle)
		* distance_walk;
	if (has_wall_at(data, new_x, new_y))
		return ;
	data->player.coord.x = new_x;
	data->player.coord.y = new_y;
	distance_side = data->player.side_direction * data->player.walk_speed;
	new_x = data->player.coord.x + cos(data->player.rotation_angle + M_PI_2)
		* distance_side;
	new_y = data->player.coord.y - sin(data->player.rotation_angle + M_PI_2)
		* distance_side;
	if (has_wall_at(data, new_x, new_y))
		return ;
	data->player.coord.x = new_x;
	data->player.coord.y = new_y;
}
