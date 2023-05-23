/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:13:25 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/23 22:16:57 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_texture_path(char *line, char **target, t_data *data)
{
	char	**new;

	new = ft_split(line, " \n");
	*target = ft_strdup(new[1]);
	data->data_count += 1;
	return (0);
}

static int	get_color(char *line, int *target, t_data *data)
{
	char	**new;

	new = ft_split(line, ", \n");
	if (!new[3])
		return (ft_error("Missing value for the RGB color"));
	target[0] = atoi(new[1]);
	target[1] = atoi(new[2]);
	target[2] = atoi(new[3]);
	data->data_count += 1;
	return (0);
}

static int	get_data(char *line, t_data *data)
{
	if (ft_strncmp(line, "\n", 1) == 0)
		return (0);
	else if (ft_strncmp(line, "NO ", 3) == 0)
		return (get_texture_path(line, &data->no, data));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (get_texture_path(line, &data->so, data));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (get_texture_path(line, &data->we, data));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (get_texture_path(line, &data->ea, data));
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (get_color(line, data->celling, data));
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (get_color(line, data->floor, data));
	return (ft_error("Invalid data in the file"));
}

static t_list	*get_file(int fd, t_data *data)
{
	char	*line;
	t_list	*lst;

	line = get_next_line(fd);
	if (!line)
	{
		ft_error("Empty file");
		return (NULL);
	}
	lst = NULL;
	while (line)
	{
		if (data->data_count == 6)
			ft_lstadd_back(&lst, ft_lstnew(line));
		else if (get_data(line, data))
			return (NULL);
		line = get_next_line(fd);
	}
	if (!lst)
		ft_error("Invalid file (map is missing)");
	return (lst);
}

int	parsing(int fd, t_data *data)
{
	t_list	*lst;

	lst = get_file(fd, data);
	if (!lst)
		return (1);
	if (check_description(data))
		return (1);
	if (check_map(&lst, data))
		return (1);
	return (0);
}
