/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:34:49 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/22 18:26:57 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logging.h"

/**
 * @brief Prints the string representation of a log level to a file descriptor.
 *
 * This function takes a log level enum value and writes its corresponding
 * string representation (e.g., "DEBUG", "INFO", "WARN", "ERROR") to the
 * specified file descriptor. It is used internally for logging purposes.
 *
 * @param level The log level to print (e.g., LOG_DEBUG, LOG_INFO, etc.).
 * @param fd Pointer to the file descriptor where the log level string will be written.
 *           The file descriptor should be open for writing.
 *
 * @return 0 on success, or a negative value on failure (e.g., write error).
 */
static int	print_log_level(t_log_level level, int *fd)
{
	if (LOGGING_LEVEL < level)
		return (0);
	if (level <= WARNING)
		*fd = STDERR_FILENO;
	if (level == ERROR)
		ft_putstr_fd(RED"[ERROR]"NC, *fd);
	else if (level == WARNING)
		ft_putstr_fd(YELLOW"[WARNING]"NC, *fd);
	else if (level == INFO)
		ft_putstr_fd(BLUE"[INFO]"NC, *fd);
	else if (level == DEBUG)
		ft_putstr_fd(MAGENTA"[DEBUG]"NC, *fd);
	return (1);
}

/**
 * @brief Starts a log message and returns file descriptor if logging is enabled
 * 
 * @param lvl The logging level
 * @param file Source file name (use __FILE__)
 * @param line Source line number (use __LINE__)
 * @return int File descriptor to write to, or -1 if logging is disabled
 */
int	log_start(t_log_level lvl, char *file, int line)
{
	int	fd;

	fd = STDOUT_FILENO;
	if (!print_log_level(lvl, &fd))
		return (-1);
	if (file && LOGGING_LEVEL == DEBUG)
	{
		ft_putstr_fd(" ("CYAN, fd);
		ft_putstr_fd(file, fd);
		ft_putstr_fd(":", fd);
		ft_putnbr_fd(line, fd);
		ft_putstr_fd(NC")", fd);
	}
	ft_putstr_fd(" -> ", fd);
	return (fd);
}

/**
 * @brief Logs a message with the specified log level, including file and line information.
 *
 * This function is used to output log messages at different levels, typically for debugging,
 * informational purposes, or error reporting. It includes the source file name and line number
 * where the log call originates.
 *
 * @param lvl The log level indicating the severity or type of the message
 * (e.g., DEBUG, INFO, WARN, ERROR).
 * 
 * @param file The name of the source file where the log is being called from.
 * 
 * @param line The line number in the source file where the log is being called from.
 * 
 * @param msg The message string to be logged.
 */
void	log_msg(t_log_level lvl, char *file, int line, char *msg)
{
	int	fd;

	fd = log_start(lvl, file, line);
	if (fd < 0)
		return ;
	if (msg)
		ft_putendl_fd(msg, fd);
}
