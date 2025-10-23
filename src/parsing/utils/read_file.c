/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:41:23 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/23 13:41:01 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	is_eof(char *line)
{
	log_msg(DEBUG, __FILE__, __LINE__, "checking for enf of file");
	if (!line)
		return (log_msg(WARNING, __FILE__, __LINE__, INVALID_PARAMETER), 1);
	if (!ft_strchr(line, '\n'))
		return (1);
	return (0);
}

static char	**read_file_content(int file_fd)
{
	char	**lines;
	int		current_line;

	log_msg(DEBUG, __FILE__, __LINE__, "reading file");
	if (file_fd < 0)
		return (log_msg(WARNING, __FILE__, __LINE__, INVALID_PARAMETER), NULL);
	lines = NULL;
	current_line = 0;
	while (1)
	{
		lines = expand_string_array(&lines);
		if (!lines)
			return (NULL);
		lines[current_line] = log_get_next_line(file_fd, __FILE__, __LINE__);
		if (!lines[current_line])
			return (free_string_array(&lines, __FILE__, __LINE__), NULL);
		if (is_eof(lines[current_line]))
			break ;
		current_line++;
	}
	return (lines);
}

char	**read_file(char *file)
{
	char	**file_content;
	int		file_fd;

	log_msg(DEBUG, __FILE__, __LINE__, "preparing to read file");
	if (!file)
		return (log_msg(ERROR, __FILE__, __LINE__, INVALID_PARAMETER), NULL);
	file_fd = open_file_read(file);
	if (file_fd < 0)
		return (NULL);
	file_content = read_file_content(file_fd);
	log_close(file_fd, __FILE__, __LINE__);
	return (file_content);
}
