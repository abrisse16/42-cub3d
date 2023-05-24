/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 22:00:18 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/24 22:29:43 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_rect(t_img *img, const t_point *start, int size, int color, int stroke_color)
{
	int	x;
	int	y;

	y = (int)start->y;
	while (y < ((int)start->y + size))
	{
		x = (int)start->x;
		while (x < ((int)start->x + size))
		{
			if (x == 0 || y == 0 || x == (int)start->x + size - 1 || y == (int)start->y + size - 1)
				my_mlx_pixel_put(img, x, y, stroke_color);
			else
				my_mlx_pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
}

t_point	create_point(float x, float y)
{
	t_point	ret;

	ret.x = x;
	ret.y = y;
	return (ret);
}