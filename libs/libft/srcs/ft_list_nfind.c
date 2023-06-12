/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_nfind.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:46:12 by ambouren          #+#    #+#             */
/*   Updated: 2023/06/12 22:46:18 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_list_nfind(t_list *lst, void *elem, size_t n,
			int (*cmp)(const void *, const void *, size_t))
{
	while (lst)
	{
		if (!cmp(lst->content, elem, n))
			return (lst);
		lst = lst->next;
	}
	return (0);
}
