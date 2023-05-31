/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 20:03:55 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/31 18:33:02 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	normalize_angle(float angle)
{
	angle = remainder(angle, 2 * M_PI);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}

static void	get_shorter_distance(t_ray *ray, t_data *data)
{
	if (ray->horz_hit_found)
		ray->horz_hit_distance = distance(data->player.coord,
				ray->horz_hit_coord);
	if (ray->vert_hit_found)
		ray->vert_hit_distance = distance(data->player.coord,
				ray->vert_hit_coord);
	if (ray->horz_hit_distance < ray->vert_hit_distance)
	{
		set_point(&ray->hit_coord, ray->horz_hit_coord.x,
			ray->horz_hit_coord.y);
		ray->hit_distance = ray->horz_hit_distance;
		ray->was_hit_horizontal = 1;
	}
	else
	{
		set_point(&ray->hit_coord, ray->vert_hit_coord.x,
			ray->vert_hit_coord.y);
		ray->hit_distance = ray->vert_hit_distance;
	}
}

static void	create_ray(t_ray *ray)
{
	ray->was_hit_horizontal = 0;
	ray->horz_hit_found = 0;
	ray->vert_hit_found = 0;
	ray->horz_hit_coord.x = 0;
	ray->horz_hit_coord.y = 0;
	ray->vert_hit_coord.x = 0;
	ray->vert_hit_coord.y = 0;
	ray->horz_hit_distance = FLT_MAX;
	ray->vert_hit_distance = FLT_MAX;
	if (ray->angle > 0 && ray->angle < M_PI)
		ray->is_facing_up = 1;
	else
		ray->is_facing_up = 0;
	if (ray->angle < M_PI / 2 || ray->angle > 3 * M_PI / 2)
		ray->is_facing_left = 0;
	else
		ray->is_facing_left = 1;
}

static void	cast_ray(t_ray *ray, t_data *data)
{
	create_ray(ray);
	horizontal_intercept(ray, data);
	vertical_intercept(ray, data);
	get_shorter_distance(ray, data);
}

void	cast_all_rays(t_data *data)
{
	int		i;
	float	ray_angle;

	i = -1;
	ray_angle = data->player.angle - (data->fov_angle / 2);
	while (++i < data->num_rays)
	{
		ray_angle = data->player.angle + atan((i - data->num_rays / 2) / data->distance_projection);
		data->rays[i].angle = normalize_angle(ray_angle);
		cast_ray(&data->rays[i], data);
	}
}
