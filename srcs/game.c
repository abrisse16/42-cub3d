/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 23:10:12 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/24 22:30:17 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>

void	render_map(t_data *data)
{
	int	x;
	int	y;
	t_point start;
	int size;
	
	size = TILE_SIZE;
	y = -1;
	while (++y < data->map.height)
	{
		x = -1;
		while (++x < data->map.width)
		{
			start = create_point((x * TILE_SIZE), (y * TILE_SIZE));
			
			if (ft_strchr("0NSWE", data->map.map[y][x]))
				draw_rect(&data->graphic.mini_map, &start, size, mlx_get_color_value(data->graphic.mlx, 0xFFFFFF), mlx_get_color_value(data->graphic.mlx, 0x0));
			// else
		}
	}
}

int	what_next(t_data *data)
{
	(void)data;
	render_map(data);
	mlx_put_image_to_window(data->graphic.mlx, data->graphic.win, data->graphic.mini_map.img, 0, 0);
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