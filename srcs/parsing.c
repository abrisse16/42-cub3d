/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:13:25 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/20 18:59:31 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_texture(char *line, char **target, t_data *data)
{
	char **new;

	new = ft_split(line, " ");
	*target = ft_strdup(new[1]);
	data->data_count += 1;
	if (data->data_count == 6)
		return (1);
	else
		return (0);
}

static int	get_color(char *line, int **target, t_data *data)
{
	char **new;

	new = ft_split(line, " ");

	data->data_count += 1;
	if (data->data_count == 6)
		return (1);
	else
		return (0);
}

static int	get_data(char *line, t_data *data)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (get_texture(line, &data->no, data));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (get_texture(line, &data->so, data));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (get_texture(line, &data->we, data));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (get_texture(line, &data->ea, data));
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (get_color(line, &data->celling, data));
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (get_color(line, &data->floor, data));
	return (0);
}

static t_list	*get_file(int fd, t_data *data)
{
	char	*line;
	t_list	*lst;
	int		have_them_all;

	line = get_next_line(fd);
	if (!line)
	{
		ft_error("Empty file");
		return (NULL);
	}
	lst = NULL;
	have_them_all = 0;
	while (line)
	{
		if (have_them_all)
			ft_lstadd_back(&lst, ft_lstnew(line));
		else
			have_them_all = get_data(line, data);
		line = get_next_line(fd);
	}
	return (lst);
}

int	parsing(int fd, t_data *data)
{
	t_list	*lst;

	lst = get_file(fd, data);
	if (!lst)
		return (1);

	
	while(lst)
	{
		printf("%s", (char *)lst->content);
		lst = lst->next;
	}
	return (0);
}
