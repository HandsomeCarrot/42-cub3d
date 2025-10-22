/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:39:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/22 16:23:27 by vpoka            ###   ########.fr       */
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
		return (NULL);
	lines = log_calloc(2, sizeof(char *), __FILE__, __LINE__);
	if (!lines)
		return (NULL);
	(void)line;
	//read all data into lines in a loop
	//each iter reallocs lines, reads a line and saves it to new lines
	return (lines);
}

/**
 * @brief reads map data out of map file
 *
 * @return 0 on success, 1 on error
 */
int	parse_map_file(char *file, t_data *data)
{
	char	**lines;
	int		fd;

	(void)data;
	log_msg(INFO, __FILE__, __LINE__, "parsing map file");
	if (correct_file_extension(file, ".cub"))
		return (1);
	lines = read_file(file);
	if (!lines)
		return (1);
	(void)fd;
	
	// parse file data
	return (0);
}
