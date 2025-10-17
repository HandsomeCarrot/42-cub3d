/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:52:41 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/17 18:19:29 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "logging.h"
# include "structs.h"
# include <mlx.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

#-----parse.c-----#

int	parse(int argc, char **argv, t_data *data);

#-----file_ops.c-----#

int	open_file_read(char *file);
int	correct_file_extension(char *file, char *extension);

#endif
