/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:31:25 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/11 19:33:30 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_map
{
	char		**layout;
	int			width;
	int			height;
}				t_map;

typedef struct s_images
{
	char		*north_wall;
	char		*east_wall;
	char		*south_wall;
	char		*west_wall;
}				t_images;

typedef struct s_colors
{
	int			ceiling;
	int			floor;
}				t_colors;

typedef struct s_player
{
	int			found;
	int			posX;
	int			posY;
	char		orientation;
}				t_player;

typedef struct s_map_data
{
	t_map		map;
	t_images	images;
	t_colors	colors;
	t_player	player;
}				t_map_data;

typedef struct s_data
{
	void		*mlx_ptr;
	t_map_data	map_data;
}				t_data;

#endif /* STRUCTS_H */
