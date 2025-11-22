/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 18:15:52 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/22 18:39:01 by vpoka            ###   ########.fr       */
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
int	open_file_read(const char *file)
{
	int	file_fd;
	int	log_fd;

	log_msg(DEBUG, __FILE__, __LINE__, "opening file for reading");
	if (!file || !*file)
	{
		log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM);
		return (-1);
	}
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
