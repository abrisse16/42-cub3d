/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:52:57 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/29 21:57:27 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_rect(t_img *img, t_to_draw *to_draw)
{
	int	x;
	int	y;
	
	y = -1;
	while (++y < to_draw->height)
	{
		x = -1;
		while (++x < to_draw->width)
			my_mlx_pixel_put(img, to_draw->x + x, to_draw->y + y, to_draw->color);
	}
}