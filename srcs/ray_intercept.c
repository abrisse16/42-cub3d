/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intercept.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 23:04:30 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/29 04:22:31 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	last_vertical_intercept(t_ray *ray, t_data *data)
{
	float next_vert_x;
	float next_vert_y;
	float tmp;
	
	tmp = 0;
	next_vert_x = ray->xintercept;
	next_vert_y = ray->yintercept;
	while (next_vert_x > 0 && next_vert_x < data->graphic.win_width
		&& next_vert_y > 0 && next_vert_y < data->graphic.win_height)
	{
		if (ray->is_facing_left)
			tmp = 1;
		if (has_wall_at(data, next_vert_x - tmp, next_vert_y))
		{
			ray->vert_hit_found = 1;
			set_point(&ray->vert_hit_coord, next_vert_x, next_vert_y);
			return ;
		}
		else
		{
			next_vert_x += ray->xstep;
			next_vert_y += ray->ystep;
		}
	}
}

void	vertical_intercept(t_ray *ray, t_data *data)
{
	ray->xintercept = floor(data->player.coord.x / TILE_SIZE) * TILE_SIZE;
	if (ray->is_facing_right)
		ray->xintercept += TILE_SIZE;
	ray->yintercept = data->player.coord.y
		+ (data->player.coord.x - ray->xintercept) * tan(ray->ray_angle);
	ray->xstep = TILE_SIZE;
	if (ray->is_facing_left)
		ray->xstep *= -1;
	ray->ystep = TILE_SIZE * tan(ray->ray_angle);
	if (ray->is_facing_up && ray->ystep > 0)
		ray->ystep *= -1;
	if (ray->is_facing_down && ray->ystep < 0)
		ray->ystep *= -1;
	last_vertical_intercept(ray, data);
}


static void	last_horizontal_intercept(t_ray *ray, t_data *data)
{
	float next_horz_x;
	float next_horz_y;
	float tmp;

	tmp = 0;
	next_horz_x = ray->xintercept;
	next_horz_y = ray->yintercept;
	while (next_horz_x > 0 && next_horz_x < data->graphic.win_width
		&& next_horz_y > 0 && next_horz_y < data->graphic.win_height)
	{
		if (ray->is_facing_up)
			tmp = 1;
		if (has_wall_at(data, next_horz_x, next_horz_y - tmp))
		{
			ray->horz_hit_found = 1;
			set_point(&ray->horz_hit_coord, next_horz_x, next_horz_y);
			return ;
		}
		else
		{
			next_horz_x += ray->xstep;
			next_horz_y += ray->ystep;
		}
	}
}

void	horizontal_intercept(t_ray *ray, t_data *data)
{
	ray->yintercept = floor(data->player.coord.y / TILE_SIZE) * TILE_SIZE;
	if (ray->is_facing_down)
		ray->yintercept += TILE_SIZE;
	ray->xintercept = data->player.coord.x
		+ (data->player.coord.y - ray->yintercept) / tan(ray->ray_angle);
	ray->ystep = TILE_SIZE;
	if (ray->is_facing_up)
		ray->ystep *= -1;
	ray->xstep = TILE_SIZE / tan(ray->ray_angle);
	if (ray->is_facing_left && ray->xstep > 0)
		ray->xstep *= -1;
	if (ray->is_facing_right && ray->xstep < 0)
		ray->xstep *= -1;
	last_horizontal_intercept(ray, data);
}
