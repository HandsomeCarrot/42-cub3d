/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:39:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/21 19:43:19 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief reads from fd until eof or error and saves all as char**
 */
static char	**read_file(char *file)
{
	char	**lines;
	char	*line;
	int		fd;

	if (!file)
		return (NULL);
	fd = open_file_read(file);
	if (fd < 0)
		return (1);
	lines = log_calloc(2, sizeof(char *), __FILE__, __LINE__);
	if (!lines)
		return (NULL);
	//read all data into lines in a loop
	//each iter reallocs lines, reads a line and saves it to new lines
}

/**
 * @brief reads map data out of map file
 *
 * @return 0 on success, 1 on error
 */
int	parse_map_file(char *file, t_data *data)
{
	char	*line;
	int		fd;

	(void)data;
	log_msg(INFO, __FILE__, __LINE__, "parsing map file\n");
	if (correct_file_extension(file, ".cub"))
		return (1);
	// read complete file
	// parse file data
}
