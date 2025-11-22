/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:31:25 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/22 14:49:11 by vpoka            ###   ########.fr       */
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
	const char		*valid_chars;
	int				limit;
	const char		*group_name;
}					t_char_group;

typedef struct s_array
{
	void			*ptr;
	size_t			capacity;
	size_t			used_space;
	size_t			member_size;
}					t_array;

typedef struct s_map
{
	char			**layout;
	int				width;
	int				height;
	int				start_line;
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

typedef enum e_log_level
{
	ERROR,
	WARNING,
	INFO,
	DEBUG
}					t_log_level;

#endif /* DEFINITIONS_H */
