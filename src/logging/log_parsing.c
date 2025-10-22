/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 20:08:44 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/22 20:36:20 by vpoka            ###   ########.fr       */
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
* @param map_file The name of the file that is invalid.
* @param source_file The source file name where the error occurred.
* @param line The line number in the source file where the error was
*             detected.
*/
void	log_extension_error(char *map_file, const char *source_file, int line)
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
