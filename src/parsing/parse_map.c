/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:39:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/22 21:01:20 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	free_string_array(char **string_array)
{
	int	pos;

	if (!string_array)
		return ;
	pos = 0;
	log_msg(DEBUG, __FILE__, __LINE__, "freeing string array");
	while (string_array[pos])
	{
		free(string_array[pos]);
		string_array[pos] = NULL;
		pos++;
	}
	free(string_array);
}

static int	is_eof(char *string, char *file, int line)
{
	log_msg(DEBUG, __FILE__, __LINE__, "checking for end of file");
	if (string && !ft_strchr(string, '\n'))
	{
		log_msg(DEBUG, file, line, "reached end of file");
		return (1);
	}
	return (0);
}

/**
 * @brief reads from file_fd until eof or error and saves all as char**
 */
static char	**read_file(char *file)
{
	int		file_fd;
	char	**lines;
	char	**tmp;
	int		line;

	if (!file)
		return (NULL);
	log_msg(DEBUG, __FILE__, __LINE__, "reading file content");
	file_fd = open_file_read(file);
	if (file_fd < 0)
		return (NULL);
	lines = NULL;
	line = 0;
	while (1)
	{
		tmp = expand_string_array(lines);
		if (!tmp)
			return (free_string_array(lines), NULL);
		lines = tmp;
		lines[line] = get_next_line(file_fd);
		if (!lines[line])
			return (free_string_array(lines), NULL);
		if (is_eof(lines[line], __FILE__, __LINE__))
			break ;
		line++;
	}
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

	(void)data;
	log_msg(INFO, __FILE__, __LINE__, "parsing map file data");
	if (correct_file_extension(file, ".cub"))
		return (1);
	lines = read_file(file);
	if (!lines)
		return (1);
	// parse file data
	return (0);
}
