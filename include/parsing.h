/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:52:41 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/23 13:18:44 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cleanup.h"
# include "get_next_line_bonus.h"
# include "logging.h"
# include "structs.h"
# include <errno.h>
# include <fcntl.h>
# include <mlx.h>
# include <string.h>

# define WHITESPACE "\t\n\v\f\r "

//-----parse.c-----//

int		parse(int argc, char **argv, t_data *data);

//-----parse_map.c-----//

int		parse_map_file(char *file, t_data *data);

//-----file_ops.c-----//

int		open_file_read(char *file);
void	log_close(int fd, const char *file, int line);
int		correct_file_extension(char *file, char *extension);

//-----read_file.c-----//

char	**read_file(char *file);

//-----expand_string_array.c-----//

char	**expand_string_array(char ***old_array);

#endif /* PARSING_H */
