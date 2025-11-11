/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:52:41 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/11 14:07:50 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cleanup.h"
# include "libft.h"
# include "logging.h"
# include "structs.h"
# include <errno.h>
# include <fcntl.h>
# include <mlx.h>
# include <stdbool.h>
# include <string.h>

# define WHITESPACE "\t\n\v\f\r "
# define MAP_TERRAIN " 01"
# define PLAYER_SPAWN "NESW"
# define MAP_LAYOUT_CHARACTERS MAP_TERRAIN PLAYER_SPAWN

# define BYTE 8

typedef enum e_color_channel
{
	RED_CHANNEL,
	GREEN_CHANNEL,
	BLUE_CHANNEL,
	ALPHA_CHANNEL
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
	int			limit;
	// For error messages
	const char		*group_name;
}					t_char_group;

typedef struct s_array
{
	//the data pointer
	void			*ptr;
	//the allocated space
	size_t			capacity;
	//the used space
	size_t			used_space;
	//size of each member
	size_t			member_size;
}					t_array;

//-----parse.c-----//

int					parse(int argc, char **argv, t_data *data);

//-----parse_map.c-----//

int					parse_map_file(char *file, t_data *data);

//-----parse_map_layout.c-----//

int	parse_map_layout(void);

//-----file_ops.c-----//

int					open_file_read(const char *file);
void				log_close(int fd, const char *file, int line);
int					correct_file_extension(const char *file,
						const char *extension);

//-----read_file.c-----//

char				**read_file(const char *file);

//-----arrays.c-----//

int	new_array(size_t member_size, size_t capacity, t_array *array);
int	expand_array(t_array *array);
int	append_to_array(void *src, t_array *array);

//-----color_utils.c-----//

int					set_color_channel(int color, t_color_channel channel,
						int value);
int					get_color_channel(int color, t_color_channel channel);

#endif /* PARSING_H */
