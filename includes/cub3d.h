/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:06:11 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/20 16:58:52 by abrisse          ###   ########.fr       */
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

typedef struct s_data
{
//	t_map		map;
//	t_game		game;
	t_graphic	graphic;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			floor[3];
	int			celling[3];
	int			data_count;
}	t_data;

/* error.c */
int	ft_error(char *str);
int	ft_perror(char *str);

/* parsing.c */
int	parsing(int fd, t_data *data);

#endif