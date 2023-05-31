/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:24:43 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/31 12:54:34 by abrisse          ###   ########.fr       */
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
