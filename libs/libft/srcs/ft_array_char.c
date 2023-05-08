/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambouren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:40:36 by ambouren          #+#    #+#             */
/*   Updated: 2023/03/16 14:40:36 by ambouren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    **ft_array_char(int nb_line, int nb_column)
{
    char    **ret;
    int     i;

    ret = (char **)ft_malloc((nb_line + 1) * sizeof(char **));
    i = -1;
    while (++i < nb_line)
    {
        ret[i] = (char *)ft_malloc(sizeof(char *) * (nb_column + 1));
        ft_bzero(ret[i], nb_column + 1);
    }
    ret[i] = 0;
    return (ret);
}