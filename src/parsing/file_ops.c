/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 18:15:52 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/22 18:18:23 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Checks if the file exists and can be opened for reading.
 *
 * This function attempts to open the specified file in read-only mode.
 * It validates the input parameter to ensure it is not NULL or empty.
 * If the file cannot be opened, an error message is logged with details.
 *
 * @param file A pointer to a null-terminated string representing the path
 *             to the file to be opened.
 * @return An integer representing the file descriptor on success (>= 0),
 *         or -1 if the file is invalid or cannot be opened.
 * @note The caller is responsible for closing the file descriptor returned
 *       on success to avoid resource leaks.
 * @warning Passing a NULL pointer or an empty string as the file parameter
 *          will result in an error and a return value of -1.
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
 * Logs an error message indicating an invalid file extension.
 * This function is used internally to report parsing errors related to file extensions.
 * @param file The name of the file that has an invalid extension.
 * @param line The line number in the source code where the error was detected.
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
 * @brief Checks if the given file has the correct extension.
 *
 * This function verifies whether the file extension of the provided filename
 * matches the specified extension. It is used to validate file types during
 * parsing operations.
 *
 * @param file A null-terminated string representing the filename to check.
 * @param extension A null-terminated string representing the expected file
 *                  extension (e.g., ".cub" for Cub3D map files).
 * @return 0 if the file extension matches, 1 on any error.
 */
int	correct_file_extension(char *file, char *extension)
{
	size_t	file_name_len;
	size_t	extension_len;
	size_t	extension_start_pos;

	if (!file || !extension)
	{
		log_msg(WARNING, __FILE__, __LINE__, "got invalid parameter");
		return (1);
	}
	file_name_len = ft_strlen(file);
	extension_len = ft_strlen(extension);
	extension_start_pos = file_name_len - extension_len;
	if (file_name_len <= extension_len
		|| file[0] == '.'
		|| ft_strncmp((file + extension_start_pos), extension, extension_len) != 0)
	{
		log_extension_error(file, __FILE__, __LINE__);
		return (1);
	}
	return (0);
}
