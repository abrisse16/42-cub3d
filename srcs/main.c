/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:04:05 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/31 23:10:14 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_args(int ac, char **av)
{
	char	*str;

	if (ac != 2)
		return (ft_error("Incorrect number of arguments"));
	str = ft_strrchr(av[1], '.');
	if (str == NULL || ft_strcmp(str, ".cub") || !ft_strcmp(av[1], ".cub"))
		return (ft_error("Invalid format file"));
	return (0);
}

void	free_graphic(t_graphic *g)
{
	if (g->north_texture.img)
		mlx_destroy_image(g->mlx, g->north_texture.img);
	if (g->south_texture.img)
		mlx_destroy_image(g->mlx, g->south_texture.img);
	if (g->west_texture.img)
		mlx_destroy_image(g->mlx, g->west_texture.img);
	if (g->east_texture.img)
		mlx_destroy_image(g->mlx, g->east_texture.img);
	if (g->game.img)
		mlx_destroy_image(g->mlx, g->game.img);
	if (g->win)
		mlx_destroy_window(g->mlx, g->win);
	if (g->mlx)
	{
		mlx_destroy_display(g->mlx);
		free(g->mlx);
	}
}

int	main(int ac, char **av)
{
	int		fd;
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	if (check_args(ac, av))
		return (1);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (ft_perror("open"));
	if (parsing(fd, &data))
	{
		close(fd);
		ft_clean_memory();
		return (1);
	}
	close(fd);
	if (init_graphic(&data))
	{
		ft_clean_memory();
		return (1);
	}
	init_data(&data);
	start(&data);
	free_graphic(&data.graphic);
	ft_clean_memory();
	return (0);
}
