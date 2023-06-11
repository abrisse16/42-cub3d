/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:00:53 by abrisse           #+#    #+#             */
/*   Updated: 2023/06/11 20:01:15 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_error(char *str)
{
	ft_putendl_fd("Error", 1);
	ft_putendl_fd(str, 1);
	return (1);
}

int	ft_perror(char *str)
{
	ft_putendl_fd("Error", 1);
	perror(str);
	return (1);
}

int	ft_perror_clean(char *str)
{
	ft_putendl_fd("Error", 1);
	perror(str);
	ft_clean_memory();
	return (1);
}
