/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:34:49 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/25 20:16:08 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/logging.h"

/**
 * @brief Prints the log level prefix if the current logging level allows it.
 *
 * This function checks if the specified log level is enabled based on the
 * LOGGING_LEVEL macro. If enabled, it sets the file descriptor to STDERR for
 * WARNING and ERROR levels, and prints a colored prefix indicating the log
 * level. For INFO and DEBUG, it uses STDOUT.
 *
 * @param level The log level to be checked and potentially printed.
 * @param fd Pointer to an integer where the appropriate file descriptor
 *           will be stored (STDOUT or STDERR).
 * @return 1 if the log level is enabled and prefix is printed, 0 otherwise.
 */
static int	print_log_level(t_log_level level, int *fd)
{
	static bool	first_error = true;

	if (LOGGING_LEVEL < level)
		return (0);
	if (level <= WARNING)
		*fd = STDERR_FILENO;
	if (level == ERROR)
	{
		if (first_error)
		{
			ft_putendl_fd("Error", *fd);
			first_error = false;
		}
		ft_putstr_fd(RED"[ERROR]"NC, *fd);
	}
	else if (level == WARNING)
		ft_putstr_fd(YELLOW"[WARNING]"NC, *fd);
	else if (level == INFO)
		ft_putstr_fd(BLUE"[INFO]"NC, *fd);
	else if (level == DEBUG)
		ft_putstr_fd(MAGENTA"[DEBUG]"NC, *fd);
	return (1);
}

/**
 * @brief Initializes and starts a log message with the specified level.
 *
 * This function prepares for logging by calling print_log_level to handle
 * the log level prefix. If the logging level is DEBUG and a file is provided,
 * it appends the file name and line number in cyan color. Finally, it prints
 * an arrow separator " -> " to indicate the start of the message content.
 *
 * @param lvl The log level for this message.
 * @param file The source file name where the log is initiated (can be NULL).
 * @param line The line number in the source file where the log is initiated.
 * @return The file descriptor to use for writing the log message, or -1 if
 *         logging is disabled for this level.
 */
int	log_start(t_log_level lvl, const char *file, int line)
{
	int	fd;

	fd = STDOUT_FILENO;
	if (!print_log_level(lvl, &fd))
		return (-1);
	if (file && LOGGING_LEVEL == DEBUG)
	{
		ft_putstr_fd(" ("CYAN, fd);
		ft_putstr_fd((char *)file, fd);
		ft_putstr_fd(":", fd);
		ft_putnbr_fd(line, fd);
		ft_putstr_fd(NC")", fd);
	}
	ft_putstr_fd(" ", fd);
	return (fd);
}

/**
 * @brief Logs a complete message with the specified level and details.
 *
 * This function combines the initialization from log_start with the actual
 * message output. It starts the log entry and, if a message is provided,
 * prints it followed by a newline to the appropriate file descriptor.
 *
 * @param lvl The log level for this message.
 * @param file The source file name where the log is initiated.
 * @param line The line number in the source file where the log is initiated.
 * @param msg The message string to be logged (can be NULL, in which case
 *            only the log header is printed).
 */
void	log_msg(t_log_level lvl, const char *file, int line, char *msg)
{
	int	fd;

	fd = log_start(lvl, file, line);
	if (fd < 0)
		return ;
	if (msg)
		ft_putendl_fd(msg, fd);
}
