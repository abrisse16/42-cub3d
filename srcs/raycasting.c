/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 20:03:55 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/29 02:10:30 by abrisse          ###   ########.fr       */
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
	ray->wall_hit.x = 0;
	ray->wall_hit.y = 0;
	ray->distance = 0;

	ray->was_hit_horizontal = 0;
	ray->was_hit_vertical = 0;
	ray->horz_wall_hit.x = 0;
	ray->horz_wall_hit.y = 0;
}

void	cast_ray(t_ray *ray, t_data *data)
{
	horizontal_intercept(ray, data);
	vertical_intercept(ray, data);
	
	// calculate both distances
	if (ray->was_hit_vertical)
	{
		ray->vert_hit_distance = distance(data->player.coord, ray->vert_wall_hit);
		printf("vert_hit_distance: %f\n", ray->vert_hit_distance);
		draw_circle(&data->graphic.mini_map, &ray->vert_wall_hit, 3, 0x0000FF);
	}
	if (ray->was_hit_horizontal)
	{
		ray->horz_hit_distance = distance(data->player.coord, ray->horz_wall_hit);
		printf("horz_hit_distance: %f\n", ray->horz_hit_distance);
		draw_circle(&data->graphic.mini_map, &ray->horz_wall_hit, 3, 0x00FF00);
	}

}

void	render_ray(t_data *data, t_ray *ray)
{
	(void)data;
	(void)ray;
}

void	cast_all_rays(t_data *data)
{
	int	i;
	t_ray	ray;
	
	ray.ray_angle = data->player.rotation_angle /* - (data->fov_angle / 2)*/;	
	i = -1;
	while(++i <= 0)
	{
		create_ray(&ray);
		cast_ray(&ray, data);
		if (i % (TILE_SIZE / 2) == 0)
			draw_orientation(&data->graphic.mini_map, ray.ray_angle, 0x0000FF, data);
		
		//render_ray(data, &ray);
		ray.ray_angle += data->fov_angle / data->num_rays;
	}
	(void)ray;
}