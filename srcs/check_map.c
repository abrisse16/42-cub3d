/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 21:34:57 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/23 22:13:49 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_empty_lines(t_list **lst)
{
	char	*line;
	t_list	*copy;

	line = (char *)(*lst)->content;
	while (ft_strncmp(line_no_space(line), "\n", 1) == 0)
	{
		(*lst) = (*lst)->next;
		if (*lst == NULL)
			return (ft_error("Invalid file (map is missing)"));
		line = (char *)(*lst)->content;
	}
	copy = *lst;
	while (copy)
	{
		if (ft_strncmp(line_no_space((char *)copy->content), "\n", 1) == 0)
			return (ft_error("Invalid file"));
		copy = copy->next;
	}
	return (0);
}

static int	check_char(t_data *data)
{
	int	i;
	int	j;

	data->map.dir = 'x';
	i = -1;
	while (data->map.map[++i])
	{
		j = -1;
		while (data->map.map[i][++j])
		{
			if (ft_strchr("01NSEW \n", data->map.map[i][j]) == NULL)
				return (ft_error("Wrong character in the map"));
			if (ft_strchr("NSEW", data->map.map[i][j]) && data->map.dir == 'x')
			{
				data->map.dir = data->map.map[i][j];
				data->player.coord.x = TILE_SIZE * j + TILE_SIZE / 2;
				data->player.coord.y = TILE_SIZE * i + TILE_SIZE / 2;
			}
			else if (ft_strchr("NSEW", data->map.map[i][j]))
				return (ft_error("The map contain multiple starting position"));
		}
	}
	return (0);
}

static int	check_error(char **map, int i, int j, t_data *data)
{
	if (i + 1 >= data->map.height)
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
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (ft_strchr("0NSEW", map[i][j]))
				if (check_error(map, i, j, data))
					return (ft_error("Map not surrouned by walls"));
		}
	}
	return (0);
}

int	check_map(t_list **lst, t_data *data)
{
	(void)data;
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
