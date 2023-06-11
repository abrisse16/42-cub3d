/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 21:34:57 by abrisse           #+#    #+#             */
/*   Updated: 2023/06/11 23:41:53 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_char(t_data *data)
{
	int	x;
	int	y;

	data->map.dir = 'x';
	y = -1;
	while (data->map.map[++y])
	{
		x = -1;
		while (data->map.map[y][++x])
		{
			if (ft_strchr("01NSEW \n", data->map.map[y][x]) == NULL)
				return (ft_error("Invalid character in the map"));
			if (ft_strchr("NSEW", data->map.map[y][x]) && data->map.dir == 'x')
			{
				data->map.dir = data->map.map[y][x];
				data->player.coord.x = TILE_SIZE * x + TILE_SIZE / 2;
				data->player.coord.y = TILE_SIZE * y + TILE_SIZE / 2;
			}
			else if (ft_strchr("NSEW", data->map.map[y][x]))
				return (ft_error("Map contain multiple starting position"));
		}
	}
	if (data->map.dir == 'x')
		return (ft_error("Missing starting position"));
	return (0);
}

static int	check_error(char **map, int i, int j, t_data *data)
{
	if (i + 1 >= data->map.height || i == 0 || j == 0)
		return (1);
	if (ft_strchr("0NSEW", map[i - 1][j]) == NULL && map[i - 1][j] != '1')
		return (1);
	if (ft_strchr("0NSEW", map[i + 1][j]) == NULL && map[i + 1][j] != '1')
		return (1);
	if (ft_strchr("0NSEW", map[i][j - 1]) == NULL && map[i][j - 1] != '1')
		return (1);
	if (ft_strchr("0NSEW", map[i][j + 1]) == NULL && map[i][j + 1] != '1')
		return (1);
	return (0);
}

static int	check_walls(char **map, t_data *data)
{
	int	y;
	int	x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (ft_strchr("0NSEW", map[y][x]))
				if (check_error(map, y, x, data))
					return (ft_error("Map not surrouned by walls"));
		}
	}
	return (0);
}

int	check_map(t_list **lst, t_data *data)
{
	if (check_empty_lines(lst))
		return (1);
	if (create_map(*lst, data))
		return (1);
	if (check_char(data))
		return (1);
	if (check_walls(data->map.map, data))
		return (1);
	return (0);
}
