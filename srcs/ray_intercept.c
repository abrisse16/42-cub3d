/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_inter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 23:04:30 by abrisse           #+#    #+#             */
/*   Updated: 2023/06/11 02:29:32 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	last_vertical_intercept(t_ray *ray, t_data *data)
{
	while (ray->inter.x > 0 && ray->inter.x < data->map.width * TILE_SIZE
		&& ray->inter.x > 0 && ray->inter.y < data->map.height * TILE_SIZE)
	{
		if (has_wall_at(data, ray->inter.x - ray->is_facing_left,
				ray->inter.y))
		{
			ray->vert_hit_found = 1;
			set_point(&ray->vert_hit_coord, ray->inter.x, ray->inter.y);
			return ;
		}
		else
		{
			ray->inter.x += ray->step.x;
			ray->inter.y += ray->step.y;
		}
	}
}

void	vertical_intercept(t_ray *ray, t_data *data)
{
	ray->inter.x = floor(data->player.coord.x / TILE_SIZE) * TILE_SIZE;
	if (!ray->is_facing_left)
		ray->inter.x += TILE_SIZE;
	ray->inter.y = data->player.coord.y
		+ (data->player.coord.x - ray->inter.x) * tan(ray->angle);
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
	while (ray->inter.x > 0 && ray->inter.x < data->map.width * TILE_SIZE
		&& ray->inter.y > 0 && ray->inter.y < data->map.height * TILE_SIZE)
	{
		if (has_wall_at(data, ray->inter.x,
				ray->inter.y - ray->is_facing_up))
		{
			ray->horz_hit_found = 1;
			set_point(&ray->horz_hit_coord, ray->inter.x, ray->inter.y);
			return ;
		}
		else
		{
			ray->inter.x += ray->step.x;
			ray->inter.y += ray->step.y;
		}
	}
}

void	horizontal_intercept(t_ray *ray, t_data *data)
{
	ray->inter.y = floor(data->player.coord.y / TILE_SIZE) * TILE_SIZE;
	if (!ray->is_facing_up)
		ray->inter.y += TILE_SIZE;
	ray->inter.x = data->player.coord.x
		+ (data->player.coord.y - ray->inter.y) / tan(ray->angle);
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
