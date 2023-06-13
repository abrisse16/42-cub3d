/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:13:25 by abrisse           #+#    #+#             */
/*   Updated: 2023/06/13 18:46:55 by ambouren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_texture_path(char *line, char **target, t_data *data)
{
	char	**new;
	int		i;

	new = ft_split(line, " \n");
	i = -1;
	while (new[++i])
		;
	if (i != 2)
		return (ft_error("Invalid file"));
	*target = ft_strdup(new[1]);
	data->data_count += 1;
	return (0);
}

static int	get_color_value(char *line, int *target, t_data *data)
{
	char	**new;
	int		i;

	new = ft_split(line, " \n");
	if (ft_nb_line_array(new) != 2)
		return (ft_error("Invalid format for the RGB color"));
	new[0] = ft_strchr(new[1], ',') + 1;
	i = 1;
	while (new[0])
	{
		new[0] = ft_strchr(new[0], ',');
		if (new[0])
			new[0]++;
		i++;
	}
	if (i != 3)
		return (ft_error("Invalid format for the RGB color"));
	new = ft_split(new[1], ",");
	if (ft_nb_line_array(new) != 3)
		return (ft_error("Invalid format for the RGB color"));
	target[0] = atoi(new[0]);
	target[1] = atoi(new[1]);
	target[2] = atoi(new[2]);
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
		return (get_color_value(line, data->celling, data));
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (get_color_value(line, data->floor, data));
	return (ft_error("Invalid file"));
}

static t_list	*get_file(int fd, t_data *data)
{
	char	*line;
	t_list	*lst;

	line = get_next_line(fd);
	if (!line)
	{
		ft_error("Invalid format file");
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
		ft_error("Invalid file");
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
