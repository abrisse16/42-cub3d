/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:06:11 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/23 23:21:00 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

# include "libft.h"
# include "mlx.h"

# define FOV_ANGLE 60	// le fov en degrés
# define TILE_SIZE 64	// taille d'une texture en gros

# define ESCAPE 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 5
# define RIGHT 6

typedef struct s_img
{
	void	*img;
	char	*data;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_point
{
	float	x;
	float	y;
}	t_point;

typedef struct s_player
{
	t_point	coord;
}	t_player;

typedef struct s_graphic
{
	void	*mlx;
	void	*win;
	int		win_width;
	int		win_height;
	t_img	mini_map;
	t_img	game;
}	t_graphic;

typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
	char	dir;
}	t_map;

typedef struct s_data
{
	t_map		map;
//	t_game		game;
	t_graphic	graphic;
	t_player	player;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			floor[3];
	int			celling[3];
	int			data_count;
	int			have_them_all;

	float		fov_angle;		

}	t_data;

/* error.c */
int	ft_error(char *str);
int	ft_perror(char *str);
int	ft_error_line(char *str, int line, int column);

/* parsing.c */
int	parsing(int fd, t_data *data);

/* check_description.c */
int	check_description(t_data *data);

/* check_map.c */
int	check_map(t_list **lst, t_data *data);

/* get_map.c */
char	*line_no_space(char *line);
int	create_map(t_list *lst, t_data *data);

/* init.c */
void	init_data(t_data *data);
int	init_window(t_data *data);

/* game.c */
void	play(t_data *data);

#endif