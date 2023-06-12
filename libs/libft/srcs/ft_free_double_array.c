/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_double_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:41:31 by ambouren          #+#    #+#             */
/*   Updated: 2023/06/12 22:46:58 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_double_array(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		ft_free(tab[i]);
	ft_free(tab);
}
