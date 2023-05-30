/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 20:35:01 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/30 20:41:47 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* fonction validée */
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
	else if (key == XK_m || key == XK_M)
		data->display_mini_map = !data->display_mini_map;
	return (0);
}

/* fonction validée */
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

/* fonction validée */
int	cross_pressed(t_data *data)
{
	mlx_loop_end(data->graphic.mlx);
	return (0);
}