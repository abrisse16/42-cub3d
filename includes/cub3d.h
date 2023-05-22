/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:06:11 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/22 23:40:28 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"
# include "mlx.h"

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_graphic
{
	void	*mlx;
	void	*win;
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
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			floor[3];
	int			celling[3];
	int			data_count;
	int			have_them_all;
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

#endif