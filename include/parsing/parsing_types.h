/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_types.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:00:00 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/28 17:09:05 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_TYPES_H
# define PARSING_TYPES_H

# include <stdbool.h>
# include <stddef.h>

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

typedef struct s_player_spawn
{
	int				found;
	int				pos_x;
	int				pos_y;
	char			orientation;
}					t_player_spawn;

typedef struct s_map_data
{
	t_map			map;
	t_images		images;
	t_colors		colors;
	t_player_spawn	player;
}					t_map_data;

#endif /* PARSING_TYPES_H */
