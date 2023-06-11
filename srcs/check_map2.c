/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 23:41:42 by abrisse           #+#    #+#             */
/*   Updated: 2023/06/11 23:47:44 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_last_lines(t_list *copy)
{
	while (copy)
	{
		if (ft_strncmp(line_no_space((char *)copy->content), "\n", 1) == 0)
		{
			while (copy->next)
			{
				copy = copy->next;
				if (ft_strncmp(line_no_space((char *)copy->content),
						"\n", 1) != 0)
					return (ft_error("Empty line(s) in the middle of the map"));
			}
		}
		copy = copy->next;
	}
	return (0);
}

int	check_empty_lines(t_list **lst)
{
	char	*line;

	line = (char *)(*lst)->content;
	while (ft_strncmp(line_no_space(line), "\n", 1) == 0)
	{
		(*lst) = (*lst)->next;
		if (*lst == NULL)
			return (ft_error("Missing map"));
		line = (char *)(*lst)->content;
	}
	if (check_last_lines(*lst))
		return (1);
	return (0);
}
