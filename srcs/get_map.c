/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 23:36:05 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/24 19:33:35 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*line_no_space(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	line += i;
	return (line);
}

static int	get_map_width(t_list *lst)
{
	int	width;
	int	max_width;

	width = 0;
	max_width = 0;
	while (lst)
	{
		width = (int)ft_strlen((char *)lst->content);
		if (((char *)lst->content)[width - 1] == '\n')
			width--;
		if (width > max_width)
			max_width = width;
		lst = lst->next;
	}
	return (max_width);
}

int	create_map(t_list *lst, t_data *data)
{
	int	i;
	int	len;

	data->map.height = ft_lstsize(lst);
	data->map.width = get_map_width(lst);
	data->map.map = ft_array_char(data->map.height, data->map.width + 1);
	if (!data->map.map)
		return (ft_perror("malloc"));
	i = -1;
	while (++i < data->map.height)
	{
		len = (int)ft_strlen((char *)lst->content);
		ft_strlcpy(data->map.map[i], (char *)lst->content, len + 1);
		lst = lst->next;
	}
	return (0);
}
