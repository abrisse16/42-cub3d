/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrisse <abrisse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:06:11 by abrisse           #+#    #+#             */
/*   Updated: 2023/05/29 05:16:12 by abrisse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <X11/keysym.h>
# include <limits.h>

# include "libft.h"
# include "mlx.h"

# define FOV_ANGLE 60					// field of view in degrees
# define TILE_SIZE 64					// size of a tile in pixels
# define MINIMAP_SCALE_FACTOR 0.3		// size of the minimap relative to the window
# define RADIUS 4						// size of the player circle on the minimap
# define WALL_STRIP_WIDTH 1				// width of a wall strip in pixels
# define WALK_SPEED 2.0f				// walk speed in pixels per frame
# define TURN_SPEED 2					// rotation speed in degrees per frame

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

typedef struct s_point
{
	float	x;
	float	y;
}	t_point;

typedef struct s_ray
{
	float	ray_angle;
	t_point	hit_coord;
	float	hit_distance;
	int		was_hit_vertical;
	int		was_hit_horizontal;
	t_point horz_hit_coord;
	t_point vert_hit_coord;
	float	xintercept;
	float	yintercept;
	float	xstep;
	float	ystep;
	int		is_facing_down;
	int		is_facing_up;
	int		is_facing_right;
	int		is_facing_left;
	int		horz_hit_found;
	int		vert_hit_found;
	float	horz_hit_distance;
	float	vert_hit_distance;
}	t_ray;

typedef struct s_player
{
	t_point	coord;
	float	rotation_angle; // rotation angle in radians
	
	int		turn_direction;
	int		walk_direction;
	int		side_direction;
	
	float	walk_speed;	// walk speed of the player in pixels per frame
	float	turn_speed;	// turn speed of the player in radians per frame
}	t_player;

typedef struct s_graphic
{
	void	*mlx;
	void	*win;
	int		win_width;
	int		win_height;
	t_img	mini_map;
	t_img	game;
	float	distance_projection;
	int		strip_x;
	int 	strip_y;
	int		strip_width;
	int		strip_height;
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
	int			num_rays;

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

/* point.c */
void	set_point(t_point *point, double x, double y);
double	distance(t_point a, t_point b);
t_point	create_point(double x, double y);

/* render.c */
void	render_minimap(t_data *data);
void	render_player(t_data *data);
int		has_wall_at(t_data *data, float new_x, float new_y);

/* draw.c */
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	draw_line(t_img *img, t_point *start, float angle, int distance);
void	draw_circle(t_img *img, t_point *center, int radius, int color);
void	draw_rect_mini(t_img *img, const t_point *start, const t_point *end, int color);
void	draw_rect(t_graphic *graphic, int color);


/* player.c */
void	update_player(t_data *data);

/* raycasting.c */
void	cast_all_rays(t_data *data);

/* ray_intercept.c */
void	horizontal_intercept(t_ray *ray, t_data *data);
void	vertical_intercept(t_ray *ray, t_data *data);

#endif