/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 20:03:55 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/29 21:56:48 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	create_ray(t_ray *ray)
{
	ray->was_hit_horizontal = 0;
	ray->was_hit_vertical = 0;
	ray->horz_hit_found	= 0;
	ray->vert_hit_found	= 0;
	ray->horz_hit_distance = FLT_MAX;
	ray->vert_hit_distance = FLT_MAX;
	if (ray->angle > 0 && ray->angle < M_PI)
		ray->is_facing_up = 1;
	else
		ray->is_facing_up = 0;
	if (ray->angle < M_PI || ray->angle > 3 * M_PI / 2)
		ray->is_facing_left = 0;
	else
		ray->is_facing_left = 1;
}

static void get_shorter_distance(t_ray *ray, t_data *data)
{
	if (ray->horz_hit_found)
		ray->horz_hit_distance = distance(data->player.coord, ray->horz_hit_coord);
	if (ray->vert_hit_found)
		ray->vert_hit_distance = distance(data->player.coord, ray->vert_hit_coord);
	if (ray->horz_hit_distance < ray->vert_hit_distance)
	{
		set_point(&ray->hit_coord, ray->horz_hit_coord.x, ray->horz_hit_coord.y);
		ray->hit_distance = ray->horz_hit_distance;
		ray->was_hit_horizontal = 1;
	}
	else
	{
		set_point(&ray->hit_coord, ray->vert_hit_coord.x, ray->vert_hit_coord.y);
		ray->hit_distance = ray->vert_hit_distance;
		ray->was_hit_vertical = 1;
	}
}

static void cast_ray(t_data *data, t_ray *ray)
{
	create_ray(ray);
	horizontal_intercept(ray, data);
	vertical_intercept(ray, data);
	get_shorter_distance(ray, data);
}

void	cast_all_rays(t_data *data)
{
	int	i;
	float	angle;
	
	i = -1;
	angle = data->player.rotation_angle - (data->fov_angle / 2);
	while (++i < data->num_rays)
	{
		data->rays[i].angle = normalize_angle(angle);
		cast_ray(data, &data->rays[i]);
		angle += data->fov_angle / data->num_rays;
	}
}