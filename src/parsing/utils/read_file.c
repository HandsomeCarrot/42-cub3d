/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:41:23 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/05 12:39:09 by vpoka            ###   ########.fr       */
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
static int	is_eof(const char *line)
{
	log_msg(DEBUG, __FILE__, __LINE__, "checking for end-of-file");
	if (!line)
		return (log_msg(WARNING, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	if (!ft_strchr(line, '\n'))
		return (1);
	return (0);
}

/**
 * @brief Reads lines from file descriptor into the array.
 *
 * This function reads lines from the file descriptor until
 * the end of file is reached, storing each line in the array.
 * Handles memory cleanup on error.
 *
 * @param file_fd The file descriptor to read from.
 * @param lines Pointer to the array structure to store lines.
 * @return 0 on success, 1 on error.
 */
static int	read_file_lines(int file_fd, t_array *lines)
{
	char	*line;
	size_t	current_line;

	current_line = 0;
	while (1)
	{
		line = log_get_next_line(file_fd, __FILE__, __LINE__);
		if (!line)
		{
			free_string_array((char ***)&lines->ptr);
			return (1);
		}
		if (append_to_array(&line, lines))
		{
			free(line);
			free_string_array((char ***)&lines->ptr);
			return (1);
		}
		if (is_eof(line))
			break ;
		current_line++;
	}
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
	t_array	lines;

	log_msg(DEBUG, __FILE__, __LINE__, "reading file");
	if (file_fd < 0)
		return (log_msg(WARNING, __FILE__, __LINE__, LOG_INVALID_PARAM), NULL);
	if (new_array(sizeof(char *), 1, &lines))
		return (NULL);
	if (read_file_lines(file_fd, &lines))
		return (NULL);
	return (lines.ptr);
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
char	**read_file(const char *file)
{
	char	**file_content;
	int		file_fd;
	int		log_fd;

	log_fd = log_start(INFO, __FILE__, __LINE__);
	if (log_fd >= 0)
	{
		ft_putstr_fd("reading from file '", log_fd);
		ft_putstr_fd((char *)file, log_fd);
		ft_putendl_fd("'", log_fd);
	}
	if (!file)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), NULL);
	file_fd = open_file_read(file);
	if (file_fd < 0)
		return (NULL);
	file_content = read_file_content(file_fd);
	log_close(file_fd, __FILE__, __LINE__);
	return (file_content);
}
