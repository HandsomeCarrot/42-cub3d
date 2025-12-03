/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 18:15:52 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/25 18:20:46 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/parsing/parsing.h"
#include <fcntl.h>

/**
 * @brief Checks if the given file path points to a directory.
 *
 * This function attempts to open the file with the O_DIRECTORY flag.
 * If the open call succeeds, it indicates the path is a directory,
 * which is treated as an error. The file descriptor is closed immediately.
 *
 * @param file The path to the file to check.
 * @return -1 if the file is a directory, 0 otherwise.
 */
static int	file_is_directory(const char *file)
{
	int	fd;
	int	log_fd;

	fd = open(file, O_RDONLY | O_DIRECTORY);
	if (fd >= 0)
	{
		log_fd = log_start(ERROR, __FILE__, __LINE__);
		if (log_fd >= 0)
		{
			ft_putstr_fd("invalid file: '", log_fd);
			ft_putstr_fd((char *)file, log_fd);
			ft_putendl_fd("': is a directory", log_fd);
		}
		close(fd);
		return (1);
	}
	return (0);
}

/**
 * @brief Opens a file for reading after validating it is not a directory.
 *
 * This function first checks if the provided path is a directory using
 * check_if_directory(). If it is not, it attempts to open the file
 * in read-only mode.
 *
 * @param file The path to the file to open.
 * @return The file descriptor if successful, or -1 on error.
 */
int	open_file_read(const char *file)
{
	int	file_fd;
	int	log_fd;

	log_msg(DEBUG, __FILE__, __LINE__, "opening file for reading");
	if (!file || !*file)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), -1);
	if (file_is_directory(file))
		return (-1);
	file_fd = open(file, O_RDONLY);
	if (file_fd < 0)
	{
		log_fd = log_start(ERROR, __FILE__, __LINE__);
		if (log_fd >= 0)
		{
			ft_putstr_fd("unable to open file '", log_fd);
			ft_putstr_fd((char *)file, log_fd);
			ft_putstr_fd("': ", log_fd);
			ft_putendl_fd(strerror(errno), log_fd);
		}
		return (-1);
	}
	return (file_fd);
}

/**
 * @brief Closes a file descriptor with error handling and logging.
 *
 * @param fd The file descriptor to close. If negative, the function
 *           performs no operation and returns silently.
 * @param file __FILE__ macro.
 * @param line __LINE__ macro.
 * @note This function logs debug messages for normal operations and
 *       warning messages for close failures. It is safe to call with
 *       invalid or already closed file descriptors.
 */
void	log_close(int fd, const char *file, int line)
{
	int	log_fd;

	log_msg(DEBUG, file, line, "closing file descriptor");
	if (fd >= 0 && close(fd) != 0)
	{
		log_fd = log_start(WARNING, file, line);
		if (log_fd >= 0)
		{
			ft_putstr_fd("failed to close file descriptor '", log_fd);
			ft_putnbr_fd(fd, log_fd);
			ft_putstr_fd("': ", log_fd);
			ft_putendl_fd(strerror(errno), log_fd);
		}
	}
}

/**
 * @brief Validates that a file has the correct extension.
 *
 * This function checks if the given file path ends with the specified
 * extension. It validates that the file is long enough to contain the
 * extension and that the extension matches exactly.
 *
 * @param file A null-terminated string of the file path to validate.
 * @param extension A null-terminated string of the expected extension,
 *                  including the leading dot (e.g., ".cub").
 * @return 0 if the file has the correct extension, 1 otherwise.
 */
static bool	has_correct_extension(const char *file, const char *extension)
{
	size_t	file_len;
	size_t	extension_len;
	size_t	file_extension;

	file_len = ft_strlen(file);
	extension_len = ft_strlen(extension);
	if (file_len <= extension_len)
		return (false);
	file_extension = file_len - extension_len;
	if (ft_strncmp((file + file_extension), extension, extension_len) != 0)
		return (false);
	return (true);
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
int	correct_file_extension(const char *file, const char *extension)
{
	char	*filename;

	log_msg(DEBUG, __FILE__, __LINE__, "validating file extension");
	if (!file || !extension)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	filename = ft_strrchr(file, '/');
	if (filename == NULL)
		filename = (char *)file;
	else
		filename++;
	if (!has_correct_extension(filename, extension))
	{
		log_invalid_file(file, extension);
		return (1);
	}
	log_msg(DEBUG, __FILE__, __LINE__, "file has valid extension");
	return (0);
}
