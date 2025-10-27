/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 20:08:44 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/27 22:59:24 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logging.h"

/**
 * @brief Logs an error message for an invalid file name.
 *
 * This static function logs an error indicating that the provided map
 * file name is invalid, typically due to incorrect extension or format.
 * It uses the logging system to output the error message.
 *
 * @param file The name of the file that is invalid.
 * @param extension the file extension that was not found in 'file'
 * @param src_file The source file name where the error occurred.
 * @param line The line number in the source file where the error was
 *             detected.
 */
void	log_extension_error(char *file, char *extension,
	const char *src_file, int line)
{
	int	log_fd;

	log_fd = log_start(ERROR, src_file, line);
	if (log_fd >= 0)
	{
		ft_putstr_fd("invalid file name: '", log_fd);
		ft_putstr_fd(file, log_fd);
		ft_putstr_fd("': '", log_fd);
		ft_putstr_fd(extension, log_fd);
		ft_putendl_fd("' extension needed", log_fd);
	}
}

/**
 * @brief Logs a line-based error with customizable message.
 *
 * This function logs an error that includes a line number and a
 * customizable error message. Useful for various parsing errors.
 *
 * @param line_num The line number where the error occurred.
 * @param message The specific error message to display.
 * @param src_file The source file name where the error occurred.
 * @param line The line number in the source file.
 */
void	log_line_error(int line_num, char *message, const char *src_file,
		int line)
{
	int	log_fd;

	log_fd = log_start(ERROR, src_file, line);
	if (log_fd >= 0)
	{
		ft_putstr_fd("in map on line ", log_fd);
		ft_putnbr_fd(line_num, log_fd);
		ft_putstr_fd(": ", log_fd);
		ft_putendl_fd(message, log_fd);
	}
}
