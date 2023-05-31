/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intercept.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 23:04:30 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/31 17:48:52 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	last_vertical_intercept(t_ray *ray, t_data *data)
{
	while (ray->intercept.x > 0 && ray->intercept.x < data->map.width * TILE_SIZE
		&& ray->intercept.x > 0 && ray->intercept.y < data->map.height * TILE_SIZE)
	{
		if (has_wall_at(data, ray->intercept.x - ray->is_facing_left,
				ray->intercept.y))
		{
			ray->vert_hit_found = 1;
			set_point(&ray->vert_hit_coord, ray->intercept.x, ray->intercept.y);
			return ;
		}
		else
		{
			ray->intercept.x += ray->step.x;
			ray->intercept.y += ray->step.y;
		}
	}
}

void	vertical_intercept(t_ray *ray, t_data *data)
{
	ray->intercept.x = floor(data->player.coord.x / TILE_SIZE) * TILE_SIZE;
	if (!ray->is_facing_left)
		ray->intercept.x += TILE_SIZE;
	ray->intercept.y = data->player.coord.y
		+ (data->player.coord.x - ray->intercept.x) * tan(ray->angle);
	ray->step.x = TILE_SIZE;
	if (ray->is_facing_left)
		ray->step.x *= -1;
	ray->step.y = TILE_SIZE * tan(ray->angle);
	if (ray->is_facing_up && ray->step.y > 0)
		ray->step.y *= -1;
	if (!ray->is_facing_up && ray->step.y < 0)
		ray->step.y *= -1;
	last_vertical_intercept(ray, data);
}

static void	last_horizontal_intercept(t_ray *ray, t_data *data)
{
	while (ray->intercept.x > 0 && ray->intercept.x < data->map.width * TILE_SIZE
		&& ray->intercept.y > 0 && ray->intercept.y < data->map.height * TILE_SIZE)
	{
		if (has_wall_at(data, ray->intercept.x,
				ray->intercept.y - ray->is_facing_up))
		{
			ray->horz_hit_found = 1;
			set_point(&ray->horz_hit_coord, ray->intercept.x, ray->intercept.y);
			return ;
		}
		else
		{
			ray->intercept.x += ray->step.x;
			ray->intercept.y += ray->step.y;
		}
	}
}

void	horizontal_intercept(t_ray *ray, t_data *data)
{
	ray->intercept.y = floor(data->player.coord.y / TILE_SIZE) * TILE_SIZE;
	if (!ray->is_facing_up)
		ray->intercept.y += TILE_SIZE;
	ray->intercept.x = data->player.coord.x
		+ (data->player.coord.y - ray->intercept.y) / tan(ray->angle);
	ray->step.y = TILE_SIZE;
	if (ray->is_facing_up)
		ray->step.y *= -1;
	ray->step.x = TILE_SIZE / tan(ray->angle);
	if (ray->is_facing_left && ray->step.x > 0)
		ray->step.x *= -1;
	if (!ray->is_facing_left && ray->step.x < 0)
		ray->step.x *= -1;
	last_horizontal_intercept(ray, data);
}
