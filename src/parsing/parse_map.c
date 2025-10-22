/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:39:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/22 22:20:08 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Frees an array of strings and sets pointers to NULL.
 *
 * This function iterates through the array of strings, freeing each
 * individual string, and then frees the array itself. It sets all
 * pointers to NULL to prevent dangling pointers.
 *
 * @param string_array A triple pointer to the array of strings to be
 *                     freed. If NULL or the array is NULL, the function
 *                     returns early without error.
 *
 * @note This function is designed to handle NULL inputs gracefully and
 *       logs debug information during the freeing process.
 */
static void	free_string_array(char ***string_array)
{
	int	pos;

	if (!string_array || !*string_array)
		return ;
	pos = 0;
	log_msg(DEBUG, __FILE__, __LINE__, "freeing string array");
	while (*string_array[pos])
	{
		free(*string_array[pos]);
		*string_array[pos] = NULL;
		pos++;
	}
	free(*string_array);
	*string_array = NULL;
}

/**
 * @brief Reads all lines from a file descriptor into a string array.
 *
 * This function reads lines from the provided file descriptor using
 * get_next_line until EOF or an error occurs. It dynamically expands
 * the array to accommodate all lines read.
 *
 * @param file The file path, used for error logging purposes.
 * @param file_fd The file descriptor to read from.
 *
 * @return A NULL-terminated array of strings containing all lines read
 *         from the file, or NULL if an error occurs during reading or
 *         memory allocation.
 *
 * @note The function stops reading when a line without a newline is
 *       encountered, assuming it as the last line. It handles memory
 *       allocation failures by freeing previously allocated memory.
 */
static char	**read_file(char *file, int file_fd)
{
	char	**lines;
	char	**tmp;
	int		line;

	log_msg(DEBUG, __FILE__, __LINE__, "reading file content");
	if (!file)
		return (log_msg(ERROR, __FILE__, __LINE__, INVALID_PARAMETER), NULL);
	lines = NULL;
	line = 0;
	while (1)
	{
		tmp = expand_string_array(lines);
		if (!tmp)
			return (free_string_array(&lines), NULL);
		lines = tmp;
		lines[line] = log_get_next_line(file_fd, __FILE__, __LINE__);
		if (!lines[line])
			return (free_string_array(&lines), NULL);
		if (!ft_strchr(lines[line], '\n'))
			break ;
		line++;
	}
	return (lines);
}

/**
 * @brief Parses map data from a specified map file.
 *
 * This function validates the file extension, opens the file for
 * reading, reads all lines into memory, and prepares for parsing the
 * map data. Currently, the actual parsing logic is not implemented.
 *
 * @param file The path to the map file with a .cub extension.
 * @param data A pointer to the data structure where parsed information
 *             should be stored (currently unused).
 *
 * @return 0 on successful parsing, 1 on error (invalid extension, file
 *         open failure, or reading failure).
 *
 * @note The function logs informational messages and ensures the file
 *       is properly closed after reading.
 */
int	parse_map_file(char *file, t_data *data)
{
	char	**lines;
	int		file_fd;

	(void)data;
	log_msg(INFO, __FILE__, __LINE__, "parsing map file data");
	if (correct_file_extension(file, ".cub"))
		return (1);
	file_fd = open_file_read(file);
	if (file_fd < 0)
		return (1);
	lines = read_file(file, file_fd);
	log_close(file_fd, __FILE__, __LINE__);
	if (!lines)
		return (1);
	// parse file data
	return (0);
}
