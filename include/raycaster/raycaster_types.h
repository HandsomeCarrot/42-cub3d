/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_types.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:00:00 by hasaliho          #+#    #+#             */
/*   Updated: 2025/11/28 17:30:06 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_TYPES_H
# define RAYCASTER_TYPES_H

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

# define P1_LOCAL_X 0.0
# define P1_LOCAL_Y 0.5
# define P2_LOCAL_X -0.3
# define P2_LOCAL_Y -0.3
# define P3_LOCAL_X 0.3
# define P3_LOCAL_Y -0.3

typedef struct s_vector
{
	double				x;
	double				y;
}						t_vector;

typedef struct s_point
{
	int					x;
	int					y;
}						t_point;

typedef struct s_player
{
	t_vector			pos;
	t_vector			look_dir;
	t_vector			plane;
	double				delta_time;
	double				speed;
}						t_player;

typedef struct s_texture
{
	void				*img;
	char				*img_data;
	int					width;
	int					height;
	int					bits_per_pixel;
	int					bytes_per_pixel;
	int					line_length;
	int					endian;
	bool				is_img_created;
	struct s_texture	*next;
}						t_texture;

typedef struct s_draw_info
{
	double				wall_x;
	int					x;
	int					y;
	int					draw_start;
	double				step;
	t_point				tex_int;
	double				tex_pos;
	t_texture			*tex;
}						t_draw_info;

typedef struct s_mlx
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*img_data;
	int					width;
	int					height;
	int					bits_per_pixel;
	int					bytes_per_pixel;
	int					line_length;
	int					endian;
}						t_mlx;

typedef struct s_ray
{
	t_vector			dir;
	t_point				map;
	t_point				step;
	t_vector			delta_dist;
	t_vector			side_dist;
	int					side;
	double				perp_wall_dist;
}						t_ray;

typedef struct s_keys
{
	bool				move_forward;
	bool				move_back;
	bool				strafe_left;
	bool				strafe_right;
	bool				rotate_left;
	bool				rotate_right;
	bool				shift;
}						t_keys;

typedef struct s_draw_ctx
{
	int					x;
	int					draw_start;
	int					draw_end;
	int					line_height;
}						t_draw_ctx;

typedef struct s_game
{
	t_mlx				mlx;
	t_player			player;
	t_keys				keys;
	char				**map;
	int					map_width;
	int					map_height;
	t_texture			north_texture;
	t_texture			south_texture;
	t_texture			east_texture;
	t_texture			west_texture;
	int					floor_color;
	int					ceiling_color;
}						t_game;

#endif /* RAYCASTER_TYPES_H */
