/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 13:25:43 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/29 00:05:47 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_orientation(t_img *img, float angle, int color, t_data *data)
{
	int		i;
	int		x;
	int		y;
	t_point	origin;

	origin.x = data->player.coord.x * MINIMAP_SCALE_FACTOR;
	origin.y = data->player.coord.y * MINIMAP_SCALE_FACTOR;
	i = 0;
	x = (int)(origin.x + cos(angle) * i);
	y = (int)(origin.y - sin(angle) * i);
	while (1)
	{
		x = (int)(origin.x + cos(angle) * i);
		y = (int)(origin.y - sin(angle) * i);
		if (has_wall_at(data, x / MINIMAP_SCALE_FACTOR,
				y / MINIMAP_SCALE_FACTOR))
			return ;
		my_mlx_pixel_put(img, x, y, color);
		i++;
	}
}

/* TO DO : Réparer les pixels qui reste dehors */
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

void	draw_rect_mini(t_img *img, const t_point *start, const t_point *end,
	int color)
{
	int	x;
	int	y;

	y = (int)start->y;
	while (y < ((int)end->y))
	{
		x = (int)start->x;
		while (x < ((int)end->x))
		{
			if (x == (int)start->x || y == (int)start->y)
				my_mlx_pixel_put(img, x, y, 0x202020);
			else
				my_mlx_pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
}
