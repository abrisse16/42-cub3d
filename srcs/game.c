/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 23:10:12 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/23 23:51:31 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	what_next(void *data)
{
	(void)data;
	
	return (0);
}

int	key_press(int key, t_data *data)
{

	if (key == ESCAPE)
		mlx_loop_end(data->graphic.mlx);
	return (0);
}

int	cross_press(t_data *data)
{
	mlx_loop_end(data->graphic.mlx);
	return (0);
}

void	play(t_data *data)
{
	mlx_loop_hook(data->graphic.mlx, what_next, data);
	mlx_hook(data->graphic.win, 17, 1L << 0, cross_press, data);
	mlx_hook(data->graphic.win, 2, 1L << 0, key_press, data);
	mlx_loop(data->graphic.mlx);
}