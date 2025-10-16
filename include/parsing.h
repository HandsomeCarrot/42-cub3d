/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:52:41 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/16 17:13:00 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "logging.h"
# include "main.h"
# include <mlx.h>

typedef struct s_mlx_image
{
	void		*img_ptr;
	int			*ret_value;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
}				t_mlx_image;

typedef struct s_rgb
{
	int			red;
	int			green;
	int			blue;
}				t_rgb;

typedef struct s_map_data
{
	char		**map;
	t_mlx_image	north_wall_image;
	t_mlx_image	east_wall_image;
	t_mlx_image	south_wall_image;
	t_mlx_image	west_wall_image;
	t_rgb		floor_color;
	t_rgb		ceiling_color;

}				t_map_data;

#endif
