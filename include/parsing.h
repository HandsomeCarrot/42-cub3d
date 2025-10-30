/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:52:41 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/30 18:31:41 by vpoka            ###   ########.fr       */
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

# define BYTE 8

typedef enum e_color_channel
{
	RED_CHANNEL,
	GREEN_CHANNEL,
	BLUE_CHANNEL,
	ALPHA_CHANNEL
}	t_color_channel;

typedef enum e_map_data_type
{
	INVALID,
	NONE,
	IMAGE,
	COLOR
}					t_map_data_type;

typedef struct s_map_id
{
	t_map_data_type	type;
	bool			found;
	const char		*id;
	int				id_len;
}					t_map_id;

//-----parse.c-----//

int					parse(int argc, char **argv, t_data *data);

//-----parse_map.c-----//

int					parse_map_file(char *file, t_data *data);

//-----file_ops.c-----//

int					open_file_read(const char *file);
void				log_close(int fd, const char *file, int line);
int					correct_file_extension(const char *file,
						const char *extension);

//-----read_file.c-----//

char				**read_file(const char *file);

//-----expand_string_array.c-----//

char				**expand_string_array(char ***old_array);

//-----color_utils.c-----//

int	set_color_channel(int color, t_color_channel channel, int value);
int	get_color_channel(int color, t_color_channel channel);

#endif /* PARSING_H */
