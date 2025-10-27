/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:41:23 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/27 17:41:44 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Checks if the given line indicates the end of a file.
 *
 * This function determines if a line read from a file represents
 * the end of the file by checking for the absence of a newline
 * character or if the line is NULL.
 *
 * @param line The line read from the file to check.
 * @return 1 if the line indicates end of file, 0 otherwise.
 */
static int	is_eof(char *line)
{
	log_msg(DEBUG, __FILE__, __LINE__, "checking for end-of-file");
	if (!line)
		return (log_msg(WARNING, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	if (!ft_strchr(line, '\n'))
		return (1);
	return (0);
}

/**
 * @brief Reads the entire content of a file into a string array.
 *
 * This function reads lines from the file descriptor until the end
 * of the file is reached, storing each line in a dynamically
 * expanding array. Logs the reading process.
 *
 * @param file_fd The file descriptor to read from.
 * @return An array of strings containing the file content, or NULL
 *         if an error occurs.
 */
static char	**read_file_content(int file_fd)
{
	char	**lines;
	int		current_line;

	log_msg(DEBUG, __FILE__, __LINE__, "reading file");
	if (file_fd < 0)
		return (log_msg(WARNING, __FILE__, __LINE__, LOG_INVALID_PARAM), NULL);
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

/**
 * @brief Reads the content of a file into a string array.
 *
 * This function opens the specified file, reads its content line
 * by line, and returns an array of strings. It handles file
 * opening, reading, and closing, with appropriate logging.
 *
 * @param file The path to the file to read.
 * @return An array of strings containing the file content, or NULL
 *         if the file cannot be opened or read.
 */
char	**read_file(char *file)
{
	char	**file_content;
	int		file_fd;

	log_msg(DEBUG, __FILE__, __LINE__, "reading file");
	if (!file)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), NULL);
	file_fd = open_file_read(file);
	if (file_fd < 0)
		return (NULL);
	file_content = read_file_content(file_fd);
	log_close(file_fd, __FILE__, __LINE__);
	return (file_content);
}
