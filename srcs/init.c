/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 21:13:34 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/30 00:24:45 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_player_rotation(t_data *data)
{
	if (data->map.dir == 'N')
		data->player.rotation_angle = M_PI_2;
	else if (data->map.dir == 'S')
		data->player.rotation_angle = 3 * M_PI_2;
	else if (data->map.dir == 'E')
		data->player.rotation_angle = 0;
	else if (data->map.dir == 'W')
		data->player.rotation_angle = M_PI;
}

static void	init_player(t_data *data)
{
	data->player.turn_direction = 0;
	data->player.walk_direction = 0;
	data->player.side_direction = 0;
	init_player_rotation(data);
	data->player.walk_speed = WALK_SPEED;
	data->player.turn_speed = TURN_SPEED * (M_PI / 180);
}

static int	init_rays(t_data *data)
{
	data->num_rays = data->graphic.win_width / WALL_STRIP_WIDTH;
	data->rays = ft_malloc(sizeof(t_ray) * data->num_rays);
	if (!data->rays)
		ft_perror("malloc");
	return (0);
}

void	init_data(t_data *data)
{
	init_player(data);
	data->graphic.win_width = TILE_SIZE * data->map.width;
	data->graphic.win_height = TILE_SIZE * data->map.height;
	data->map.map[(int)data->player.coord.y / TILE_SIZE]
		[(int)data->player.coord.x / TILE_SIZE] = '0';
	data->fov_angle = FOV_ANGLE * (M_PI / 180);
	data->graphic.distance_projection = (data->graphic.win_width / 2)
		/ tan(data->fov_angle / 2);
}

static int	init_img(void *mlx, t_img *img, int width, int height)
{
	img->img = mlx_new_image(mlx, width, height);
	if (!img->img)
		return (ft_error("mlx_new_image: Failed"));
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
	return (0);
}

static int	get_textures(void *mlx, char *path, t_img *img)
{
	img->img = mlx_xpm_file_to_image(mlx, path, &img->width, &img->height); // img->img
	if (!img->img)
		return (ft_error("mlx_xpm_file_to_image: Failed"));
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
	return (0);
}

static int	init_textures(void *mlx, t_graphic *g, t_data *data)
{
	if (get_textures(mlx, data->no, &g->north_texture)
		|| get_textures(mlx, data->so, &g->south_texture)
		|| get_textures(mlx, data->we, &g->west_texture)
		|| get_textures(mlx, data->ea, &g->east_texture))
		return (1);
	return (0);
}

int	init_graphic(t_data *data)
{
	if (init_rays(data))
		return (1);
	data->graphic.mlx = mlx_init();
	if (!data->graphic.mlx)
		return (ft_error("mlx_init: Failed"));
	if (init_textures(data->graphic.mlx, &data->graphic, data))
		return (1);
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
