/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:34:49 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/21 19:19:55 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logging.h"

/**
 * @brief Prints the logging level tag to standard error output.
 *
 * This static helper function checks if the global LOGGING_LEVEL is high
 * enough to allow logging at the requested level. If allowed, it prints
 * the corresponding log level tag (e.g., [ERROR], [WARNING]) to stderr.
 *
 * @param level The logging level to print.
 *
 * @return 1 if the logging level is allowed and printed, 0 otherwise.
 */
static int	print_log_level(t_log_level level, int *fd)
{
	if (LOGGING_LEVEL < level)
		return (0);
	if (level <= WARNING)
		*fd = STDERR_FILENO;
	if (level == ERROR)
		ft_putstr_fd("[ERROR]", *fd);
	else if (level == WARNING)
		ft_putstr_fd("[WARNING]", *fd);
	else if (level == INFO)
		ft_putstr_fd("[INFO]", *fd);
	else if (level == DEBUG)
		ft_putstr_fd("[DEBUG]", *fd);
	return (1);
}

/**
 * @brief Prints a formatted log message to standard error with context.
 *
 * This function prints a log message to stderr if the specified logging
 * level is enabled. It includes the log level tag, the source file name,
 * and the line number where the log_msg function was called, followed by
 * the user-provided message.
 *
 * The `file` and `line` parameters should be passed using the `__FILE__`
 * and `__LINE__` macros respectively to provide accurate source location.
 * DOES NOT PRINT A NEWLINE CHARACTER!
 *
 * @param lvl The logging level of the message (ERROR, WARNING, INFO, DEBUG).
 * @param file The source file name where log_msg() was called. Typically
 *             passed as the `__FILE__` macro.
 * @param line The line number in the source file where log_msg() was called.
 *             Typically passed as the `__LINE__` macro.
 * @param msg The message string to print.
 * 
 * @note - use ft_putstr_fd(), ft_putnbr_fd(), ft_putendl_fd() to make
 * message longer
 * @note - only prints to standard error
 */
void	log_msg(t_log_level lvl, char *file, int line, char *msg)
{
	int	fd;

	fd = STDOUT_FILENO;
	if (!print_log_level(lvl, &fd))
		return ;
	if (file)
	{
		ft_putstr_fd(": ", fd);
		ft_putstr_fd(file, fd);
		ft_putstr_fd(":", fd);
		ft_putnbr_fd(line, fd);
	}
	if (msg)
	{
		ft_putstr_fd(" -> ", fd);
		ft_putstr_fd(msg, fd);
	}
}
