/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:57:12 by hasaliho          #+#    #+#             */
/*   Updated: 2025/10/29 08:26:07 by hasaliho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>

typedef struct s_vector
{
	double		x;
	double		y;
}				t_vector;

typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct s_player
{
	t_vector	pos;
	t_vector	look_dir;
	t_vector	plane;
	double		delta_time;
	double		speed;
}				t_player;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*img_data;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx;

typedef struct s_ray
{
    t_vector    dir;
    t_point     map;
    t_point     step;
    t_vector    delta_dist;
    t_vector    side_dist;
    int         side;
    double      perp_wall_dist;
}   t_ray;

typedef struct s_keys
{
	bool	move_forward;
	bool	move_back;
	bool	strafe_left;
	bool	strafe_right;
	bool	rotate_left;
	bool	rotate_right;
	bool	shift;
}	t_keys;

typedef struct s_texture
{
	void	*img;
	char	*img_data;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_texture;

typedef struct s_game
{
	t_mlx		mlx;
	t_player	player;
	t_keys		keys;
	char		**map;
	t_texture	north_texture;
	t_texture	south_texture;
	t_texture	east_texture;
	t_texture	west_texture;
	int			floor_color;
	int			ceiling_color;
}	t_game;

#endif
