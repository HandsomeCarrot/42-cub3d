/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:57:12 by hasaliho          #+#    #+#             */
/*   Updated: 2025/10/21 11:16:48 by hasaliho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdio.h>
# include <stdlib.h>

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

typedef struct s_game
{
	t_mlx		mlx;
	t_player	player;
	char		**map;
}	t_game;

#endif
