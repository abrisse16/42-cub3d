/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intercept.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 23:04:30 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/29 02:16:29 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	last_vertical_intercept(t_ray *ray, t_data *data)
{
	float	next_vert_x;
	float	next_vert_y;
	int		is_left;

	next_vert_x = ray->xintercept;
	next_vert_y = ray->yintercept;

	// if facing left alors -1
	if (ray->ray_angle > M_PI / 2 && ray->ray_angle < 3 * M_PI / 2)
		is_left = 1;
	while (next_vert_x > 0 && next_vert_x < data->graphic.win_width
		&& next_vert_y > 0 && next_vert_y < data->graphic.win_height)
	{
		if (has_wall_at(data, next_vert_x - is_left, next_vert_y))
		{
			ray->was_hit_vertical = 1;
			set_point(&ray->vert_wall_hit, next_vert_x, next_vert_y);
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
	if (ray->ray_angle < M_PI / 2 || ray->ray_angle > 3 * M_PI / 2)
		ray->xintercept += TILE_SIZE;
	ray->yintercept = data->player.coord.y
		+ (data->player.coord.x - ray->xintercept) * tan(ray->ray_angle);
	ray->xstep = TILE_SIZE;
	if (ray->ray_angle > M_PI / 2 && ray->ray_angle < 3 * M_PI / 2)
		ray->xstep *= -1;
	ray->ystep = TILE_SIZE / tan(ray->ray_angle);
	if (ray->ray_angle < M_PI / 2 || ray->ray_angle > 3 * M_PI / 2)
		ray->ystep *= -1;
	last_vertical_intercept(ray, data);
}

static void	last_horizontal_intercept(t_ray *ray, t_data *data)
{
	float	next_horz_x;
	float	next_horz_y;
	int		is_up;

	next_horz_x = ray->xintercept;
	next_horz_y = ray->yintercept;
	if (ray->ray_angle < M_PI)
		is_up = -1;
	else
		is_up = 1;
	while (next_horz_x > 0 && next_horz_x < data->graphic.win_width
		&& next_horz_y > 0 && next_horz_y < data->graphic.win_height)
	{
		if (has_wall_at(data, next_horz_x, next_horz_y + is_up))
		{
			ray->was_hit_horizontal = 1;
			set_point(&ray->horz_wall_hit, next_horz_x, next_horz_y);
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
	if (ray->ray_angle > M_PI)
		ray->yintercept += TILE_SIZE;
	ray->xintercept = data->player.coord.x
		+ (data->player.coord.y - ray->yintercept) / tan(ray->ray_angle);
	ray->ystep = TILE_SIZE;
	if (ray->ray_angle < M_PI)
		ray->ystep *= -1;
	ray->xstep = TILE_SIZE / tan(ray->ray_angle);
	if (ray->ray_angle > M_PI)
		ray->xstep *= -1;
	last_horizontal_intercept(ray, data);
}
