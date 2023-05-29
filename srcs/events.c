/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:25:34 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/29 16:04:08 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_pressed(int key, t_data *data)
{
	if (key == XK_Escape)
		mlx_loop_end(data->graphic.mlx);
	else if (key == XK_w || key == XK_W)
		data->player.walk_direction = 1;
	else if (key == XK_s || key == XK_S)
		data->player.walk_direction = -1;
	else if (key == XK_a || key == XK_A)
		data->player.side_direction = 1;
	else if (key == XK_d || key == XK_D)
		data->player.side_direction = -1;
	else if (key == XK_Left)
		data->player.turn_direction = 1;
	else if (key == XK_Right)
		data->player.turn_direction = -1;
	return (0);
}

int	key_released(int key, t_data *data)
{
	if (key == XK_w || key == XK_W)
		data->player.walk_direction = 0;
	else if (key == XK_s || key == XK_S)
		data->player.walk_direction = 0;
	else if (key == XK_a || key == XK_A)
		data->player.side_direction = 0;
	else if (key == XK_d || key == XK_D)
		data->player.side_direction = 0;
	else if (key == XK_Left)
		data->player.turn_direction = 0;
	else if (key == XK_Right)
		data->player.turn_direction = 0;
	return (0);
}

int	cross_pressed(t_data *data)
{
	mlx_loop_end(data->graphic.mlx);
	return (0);
}