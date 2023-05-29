/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 22:00:18 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/29 02:01:53 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_point(t_point *point, double x, double y)
{
	point->x = x;
	point->y = y;
}

double	distance(t_point a, t_point b)
{
	return (sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2)));
}

t_point	create_point(double x, double y)
{
	t_point	ret;

	ret.x = x;
	ret.y = y;
	return (ret);
}
