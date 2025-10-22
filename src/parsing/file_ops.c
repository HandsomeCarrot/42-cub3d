/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 18:15:52 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/22 18:46:53 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Opens a file for reading and returns its file descriptor.
 *
 * This function validates the input file path, attempts to open the file
 * in read-only mode, and returns the file descriptor. If the file cannot
 * be opened, it logs an error message including the system error
 * description and returns -1.
 *
 * @param file A null-terminated string representing the path to the file
 *             to be opened. Must not be NULL or empty.
 * @return The file descriptor of the opened file on success, or -1 if
 *         the file could not be opened or if invalid parameters were
 *         provided.
 * @note This function logs warnings for invalid parameters and errors
 *       for file opening failures using the logging system.
 */
int	open_file_read(char *file)
{
	int	file_fd;
	int	log_fd;

	if (!file || !*file)
	{
		log_msg(WARNING, __FILE__, __LINE__, "got invalid parameter");
		return (-1);
	}
	file_fd = open(file, O_RDONLY);
	if (file_fd < 0)
	{
		log_fd = log_start(ERROR, __FILE__, __LINE__);
		if (log_fd >= 0)
		{
			ft_putstr_fd("unable to open file '", log_fd);
			ft_putstr_fd(file, log_fd);
			ft_putstr_fd("': ", log_fd);
			ft_putendl_fd(strerror(errno), log_fd);
		}
		return (-1);
	}
	return (file_fd);
}

/**
	* @brief Logs an error message for an invalid file name.
	*
	* This static function logs an error indicating that the provided map
	* file name is invalid, typically due to incorrect extension or format.
	* It uses the logging system to output the error message.
	*
	* @param map_file The name of the file that is invalid.
	* @param source_file The source file name where the error occurred.
	* @param line The line number in the source file where the error was
	*             detected.
	*/
static void	log_extension_error(char *map_file, char *source_file, int line)
{
	int	log_fd;

	log_fd = log_start(ERROR, source_file, line);
	if (log_fd >= 0)
	{
		ft_putstr_fd("invalid file name '", log_fd);
		ft_putstr_fd(map_file, log_fd);
		ft_putendl_fd("'", log_fd);
	}
}

/**
	* @brief Validates that a file has the correct extension.
	*
	* This function checks if the given file path ends with the specified
	* extension. It performs several validations: ensures the file and
	* extension strings are not NULL, checks that the file name is not
	* just an extension (starts with '.'), and verifies that the file
	* ends with the exact extension string.
	*
	* @param file A null-terminated string of the file path to validate.
	* @param extension A null-terminated string of the expected extension,
	*                  including the leading dot (e.g., ".cub").
	* @return 0 if the file has the correct extension, 1 otherwise.
	* @note This function logs a warning for invalid parameters and an
	*       error for incorrect file extensions.
	*/
int	correct_file_extension(char *file, char *extension)
{
	size_t	file_len;
	size_t	extension_len;
	size_t	file_extension;

	if (!file || !extension)
	{
		log_msg(WARNING, __FILE__, __LINE__, "got invalid parameter");
		return (1);
	}
	file_len = ft_strlen(file);
	extension_len = ft_strlen(extension);
	file_extension = file_len - extension_len;
	if (file_len <= extension_len || file[0] == '.'
		|| ft_strncmp((file + file_extension), extension, extension_len) != 0)
	{
		log_extension_error(file, __FILE__, __LINE__);
		return (1);
	}
	return (0);
}
