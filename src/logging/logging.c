/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:34:49 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/16 19:07:40 by vpoka            ###   ########.fr       */
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
static int	print_log_level(t_log_level level)
{
	if (LOGGING_LEVEL < level)
		return (0);
	if (level == ERROR)
		ft_putstr_fd("[ERROR]", STDERR_FILENO);
	else if (level == WARNING)
		ft_putstr_fd("[WARNING]", STDERR_FILENO);
	else if (level == INFO)
		ft_putstr_fd("[INFO]", STDERR_FILENO);
	else if (level == DEBUG)
		ft_putstr_fd("[DEBUG]", STDERR_FILENO);
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
 */
void	log_msg(t_log_level lvl, char *file, int line, char *msg)
{
	if (!print_log_level(lvl))
		return ;
	if (file)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putstr_fd(":", STDERR_FILENO);
		ft_putnbr_fd(line, STDERR_FILENO);
	}
	if (msg)
	{
		ft_putstr_fd(" -> ", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
	}
}
