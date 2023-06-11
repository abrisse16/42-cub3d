/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 15:59:12 by abrisse           #+#    #+#             */
/*   Updated: 2023/06/11 16:07:47 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_color_x(t_ray *ray, t_texture_data *texture_data, t_img texture)
{
	if (ray->was_hit_horizontal)
	{
		if (ray->is_facing_up)
			texture_data->color_x = ((int)ray->hit_coord.x % TILE_SIZE)
				* (texture.width / TILE_SIZE);
		else
			texture_data->color_x = (TILE_SIZE - 1 - ((int)ray->hit_coord.x
						% TILE_SIZE)) * (texture.width / TILE_SIZE);
	}
	else
	{
		if (ray->is_facing_left)
			texture_data->color_x = (TILE_SIZE - 1 - ((int)ray->hit_coord.y
						% TILE_SIZE)) * (texture.width / TILE_SIZE);
		else
			texture_data->color_x = ((int)ray->hit_coord.y % TILE_SIZE)
				* (texture.width / TILE_SIZE);
	}
}

void	get_color_y(t_ray *ray, t_data *data, t_texture_data *texture_data,
	t_img texture)
{
	ray->distance_from_top = ray->y
		+ ((int)ray->projected_height / 2)
		- (data->graph.win_height / 2);
	texture_data->color_y = ray->distance_from_top * ((float)texture.height
			/ (int)ray->projected_height);
}

int	get_color(t_texture_data *texture_data, t_img texture)
{
	return (*(int *)(texture.addr + (texture_data->color_y
			* texture.line_len + texture_data->color_x
			* (texture.bpp / 8))));
}
