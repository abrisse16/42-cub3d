/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 20:03:55 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/29 05:19:55 by abrisse          ###   ########.fr       */
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

void	create_ray(t_ray *ray)
{
	ray->ray_angle = normalize_angle(ray->ray_angle);
	ray->was_hit_horizontal = 0;
	ray->was_hit_vertical = 0;
	ray->horz_hit_found = 0;
	ray->vert_hit_found = 0;
	ray->is_facing_down = 0;
	ray->is_facing_up = 0;
	ray->is_facing_left = 0;
	ray->is_facing_right = 0;
	if (ray->ray_angle > 0 && ray->ray_angle < M_PI)
		ray->is_facing_up = 1;
	else
		ray->is_facing_down = 1;
	if (ray->ray_angle < M_PI / 2 || ray->ray_angle > 3 * M_PI / 2)
		ray->is_facing_right = 1;
	else
		ray->is_facing_left = 1;
	ray->horz_hit_coord.x = 0;
	ray->horz_hit_coord.y = 0;
	ray->vert_hit_coord.x = 0;
	ray->vert_hit_coord.y = 0;
}

void	get_shorter_distance(t_ray *ray, t_data *data)
{
	if (ray->horz_hit_found)
		ray->horz_hit_distance = distance(data->player.coord, ray->horz_hit_coord);
	else
		ray->horz_hit_distance = INT_MAX;
	if (ray->vert_hit_found)
		ray->vert_hit_distance = distance(data->player.coord, ray->vert_hit_coord);
	else
		ray->vert_hit_distance = INT_MAX;
	if (ray->horz_hit_distance < ray->vert_hit_distance)
	{
		set_point(&ray->hit_coord, ray->horz_hit_coord.x, ray->horz_hit_coord.y);
		ray->hit_distance = ray->horz_hit_distance;
	}
	else
	{
		set_point(&ray->hit_coord, ray->vert_hit_coord.x, ray->vert_hit_coord.y);
		ray->hit_distance = ray->vert_hit_distance;
	}
}

void	cast_ray(t_ray *ray, t_data *data)
{
	horizontal_intercept(ray, data);
	vertical_intercept(ray, data);
	get_shorter_distance(ray, data);
}

void	render_ray(t_data *data, t_ray *ray, int i)
{
	float	strip_height;
	float	new_distance;

	
	(void)data;
	(void)ray;
	new_distance = ray->hit_distance * cos(ray->ray_angle - data->player.rotation_angle);
	strip_height = (TILE_SIZE / new_distance) * data->graphic.distance_projection;

	data->graphic.strip_x = i * WALL_STRIP_WIDTH;
	data->graphic.strip_y = (data->graphic.win_height / 2) - (strip_height / 2);
	data->graphic.strip_width = WALL_STRIP_WIDTH;
	data->graphic.strip_height = strip_height;

	printf("strip_x: %d\n", data->graphic.strip_x);
	printf("strip_y: %d\n", data->graphic.strip_y);
	printf("strip_width: %d\n", data->graphic.strip_width);
	printf("strip_height: %d\n", data->graphic.strip_height);
	draw_rect(&data->graphic, 0x00FF00);
}

void	cast_all_rays(t_data *data)
{
	int	i;
	t_ray	ray;
	
	ray.ray_angle = data->player.rotation_angle - (data->fov_angle / 2);	
	i = -1;
	while(++i <= data->num_rays)
	{
		create_ray(&ray);
		cast_ray(&ray, data);
		if (i % (TILE_SIZE / 2) == 0)
			draw_line(&data->graphic.mini_map, &data->player.coord, ray.ray_angle, ray.hit_distance);
		render_ray(data, &ray, i);
		ray.ray_angle += data->fov_angle / data->num_rays;
	}
	(void)ray;
}