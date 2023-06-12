/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_one_if.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambouren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:43:38 by ambouren          #+#    #+#             */
/*   Updated: 2023/03/16 14:43:38 by ambouren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_list_remove_one_if(t_list **lst, void *elem,
			int (*cmp)(), void (*del)(void *))
{
	t_list	*to_del;

	to_del = ft_lstremove_elem(lst, elem, cmp);
	del(to_del->content);
	ft_free(to_del);
}
