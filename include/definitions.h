/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:31:25 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/21 19:46:07 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINITIONS_H
# define DEFINITIONS_H

# include <stdbool.h>
# include <stddef.h>

# define WHITESPACE "\t\n\v\f\r "

# define MAP_PADDING " "
# define MAP_TERRAIN "01"
# define PLAYER_SPAWN "NESW"
# define MAP_LAYOUT_CHARACTERS " 01NESW"

# define BYTE 8

typedef enum e_color_channel
{
	RED_CH,
	GREEN_CH,
	BLUE_CH,
	ALPHA_CH
}					t_color_channel;

typedef enum e_map_data_type
{
	INVALID,
	NONE,
	TEXTURE,
	T_IMAGE,
	T_COLOR,
	MAP
}					t_map_data_type;

typedef struct s_map_id
{
	t_map_data_type	type;
	bool			found;
	const char		*id;
	int				id_len;
}					t_map_id;

typedef struct s_char_group
{
	// Characters in this group
	const char		*valid_chars;
	// -1 = unlimited, 0 = not allowed, 1+ = specific limit
	int				limit;
	// For error messages
	const char		*group_name;
}					t_char_group;

typedef struct s_array
{
	// the data pointer
	void			*ptr;
	// the allocated space
	size_t			capacity;
	// the used space
	size_t			used_space;
	// size of each member
	size_t			member_size;
}					t_array;

typedef struct s_map
{
	char			**layout;
	int				width;
	int				height;
}					t_map;

typedef struct s_images
{
	char			*north_wall;
	char			*east_wall;
	char			*south_wall;
	char			*west_wall;
}					t_images;

typedef struct s_colors
{
	int				ceiling;
	int				floor;
}					t_colors;

typedef struct s_player
{
	int				found;
	int				pos_x;
	int				pos_y;
	char			orientation;
}					t_player;

typedef struct s_map_data
{
	t_map			map;
	t_images		images;
	t_colors		colors;
	t_player		player;
}					t_map_data;

typedef struct s_data
{
	void			*mlx_ptr;
	t_map_data		map_data;
}					t_data;

#endif /* DEFINITIONS_H */
