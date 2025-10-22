/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:52:41 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/22 18:43:45 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

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

//-----file_ops.c-----//

int		open_file_read(char *file);
int		correct_file_extension(char *file, char *extension);

//-----expand_string_array.c-----//

char	**expand_string_array(char **old_array);

#endif /* PARSING_H */
