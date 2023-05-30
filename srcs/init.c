/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 21:13:34 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/30 12:06:31 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_player_rotation(t_data *data)
{
	if (data->map.dir == 'N')
		data->player.rotation_angle = M_PI / 2;
	else if (data->map.dir == 'S')
		data->player.rotation_angle = 3 * M_PI / 2;
	else if (data->map.dir == 'W')
		data->player.rotation_angle = M_PI;
	else if (data->map.dir == 'E')
		data->player.rotation_angle = 0;
}

void	init_data(t_data *data)
{
	data->graphic.win_width = TILE_SIZE * data->map.width;
	data->graphic.win_height = TILE_SIZE * data->map.height;
	data->map.map[(int)data->player.coord.y / TILE_SIZE][(int)data->player.coord.x / TILE_SIZE] = '0';
	data->fov_angle = FOV_ANGLE * (M_PI / 180);
	data->num_rays = data->graphic.win_width / WALL_STRIP_WIDTH;
	data->player.turn_direction = 0;
	data->player.walk_direction = 0;
	data->player.side_direction = 0;
	init_player_rotation(data);
	data->player.walk_speed = WALK_SPEED;
	data->player.turn_speed = TURN_SPEED * (M_PI / 180);
	data->graphic.distance_projection = (data->graphic.win_width / 2) / tan(data->fov_angle / 2);
}

int	init_img(void *mlx, t_img *img, int width, int height)
{
	img->img = mlx_new_image(mlx, width, height);
	if (!img->img)
		return (ft_error("mlx_new_image: Failed"));
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
	return (0);
}

int	init_window(t_data *data)
{
	data->graphic.mlx = mlx_init();
	if (!data->graphic.mlx)
		return (ft_error("mlx_init: Failed"));
	data->graphic.win = mlx_new_window(data->graphic.mlx,
			data->graphic.win_width, data->graphic.win_height, "cub3D");
	if (!data->graphic.win)
		return (ft_error("mlx_new_window: Failed"));
	if (init_img(data->graphic.mlx, &data->graphic.mini_map,
			data->graphic.win_width * MINIMAP_SCALE_FACTOR, data->graphic.win_height * MINIMAP_SCALE_FACTOR))
		return (1);
	if (init_img(data->graphic.mlx, &data->graphic.game,
			data->graphic.win_width, data->graphic.win_height))
		return (1);
	return (0);
}
