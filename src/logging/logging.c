/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:34:49 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/15 20:41:46 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logging.h"

/**
 * @brief Prints the logging level to stderr.
 *
 * If the LOGGING_LEVEL is set high enough for requested logging level,
 * it will print the defined message for that level to stderr.
 *
 * @param level the requested logging level.
 *
 * @return 1 if logging level is allowed, 0 otherwise.
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
 * @brief Prints a message to stderr with some extra info.
 *
 * It prints a formatted message with the extra info and the message,
 * if the logging level is high enough.
 *
 * @param file the file name where log_msg() got called.
 * @param line the line in which log_msg() got called in.
 * @param lvl the logging level of the message (ERROR, WARNING, INFO, DEBUG)
 * @param msg the message to print
 */
void	log_msg(t_log_level lvl, char *file, int line, char *msg)
{
	if (!print_log_level(lvl))
		return ;
	if (file || line)
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
	ft_putchar_fd('\n', STDERR_FILENO);
}
