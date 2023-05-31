/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 13:25:43 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/31 12:48:29 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_color_rect(t_img *img, t_to_draw *to_draw)
{
	int	x;
	int	y;

	y = -1;
	while (++y < to_draw->height)
	{
		x = -1;
		while (++x < to_draw->width)
			my_mlx_pixel_put(img, to_draw->x + x, to_draw->y + y,
				to_draw->color);
	}
}

void	draw_ray(t_img *img, t_point *start, float angle, int distance)
{
	int	i;
	int	x;
	int	y;

	i = -1;
	while (++i < distance * MINIMAP_SCALE_FACTOR)
	{
		x = (int)((start->x * MINIMAP_SCALE_FACTOR) + cos(angle) * i);
		y = (int)((start->y * MINIMAP_SCALE_FACTOR) - sin(angle) * i);
		my_mlx_pixel_put(img, x, y, 0x0000FF);
	}
}

void	draw_circle(t_img *img, t_point *center, int radius, int color)
{
	int	pos_x;
	int	pos_y;
	int	x;
	int	y;

	pos_x = (int)center->x * MINIMAP_SCALE_FACTOR;
	pos_y = (int)center->y * MINIMAP_SCALE_FACTOR;
	y = pos_y - radius;
	while (y <= pos_y + radius)
	{
		x = pos_x - radius;
		while (x <= pos_x + radius)
		{
			if ((x - pos_x) * (x - pos_x) + (y - pos_y)
				* (y - pos_y) <= radius * radius)
				my_mlx_pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
}
