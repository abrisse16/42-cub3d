/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _game.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 23:10:12 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/29 14:25:52 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_celling_and_floor(t_data *data)
{
	draw_background(&data->graphic.game, mlx_get_color_value(data->graphic.mlx, 0xFF0000), data, 'C');
	draw_background(&data->graphic.game, mlx_get_color_value(data->graphic.mlx, 0x0000FF), data, 'F');
}

int	what_next(t_data *data)
{
	update_player(data);
	render_minimap(data);
	render_celling_and_floor(data);
	cast_all_rays(data);
	render_player(data);
	mlx_put_image_to_window(data->graphic.mlx, data->graphic.win,
		data->graphic.game.img, 0, 0);
	mlx_put_image_to_window(data->graphic.mlx, data->graphic.win,
		data->graphic.mini_map.img, 0, 0);
	return (0);
}

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

void	play(t_data *data)
{
	mlx_loop_hook(data->graphic.mlx, what_next, data);
	mlx_hook(data->graphic.win, 17, 1L << 0, cross_pressed, data);
	mlx_hook(data->graphic.win, 2, 1L << 0, key_pressed, data);
	mlx_hook(data->graphic.win, 3, 1L << 1, key_released, data);
	mlx_loop(data->graphic.mlx);
}
