/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:00:53 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/22 23:41:46 by abrisse          ###   ########.fr       */
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

int	ft_error_line(char *str, int line, int column)
{
	ft_putendl_fd("Error", 1);
	ft_putnbr_fd(line, 1);
	ft_putchar_fd(':', 1);
	ft_putnbr_fd(column, 1);
	ft_putstr_fd(": ", 1);
	ft_putendl_fd(str, 1);
	return (1);
}
