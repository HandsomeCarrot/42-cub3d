/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 19:28:02 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/22 13:13:48 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief checks if the 'line' only consists of whitespace characters
 *
 * @param line string to check
 *
 * @return true if it is empty, false otherwise
 */
bool	is_empty_line(char *line)
{
	size_t	pos;

	if (!line)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), false);
	log_msg(DEBUG, __FILE__, __LINE__, "checking for empty line");
	pos = 0;
	while (line[pos])
	{
		if (!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!is_whitespace(line[pos]))
		{
			log_msg(DEBUG, __FILE__, __LINE__, "not a empty line");
			return (false);
		}
		pos++;
	}
	log_msg(DEBUG, __FILE__, __LINE__, "is a empty line");
	return (true);
}

/**
 * @brief Checks if a line has leading whitespace.
 *
 * Logs an error if leading whitespace is found before map data.
 *
 * @param line The line to check.
 * @param row The line number for error reporting.
 * @return true if leading whitespace found, false otherwise.
 */
bool	has_leading_whitespace(char *line, int row)
{
	if (!line)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), true);
	log_msg(DEBUG, __FILE__, __LINE__, "checking for leading whitespaces");
	if (is_whitespace(line[0]))
	{
		log_line_error(row, "leading whitespace before map data", __FILE__,
			__LINE__);
		return (true);
	}
	log_msg(DEBUG, __FILE__, __LINE__, "no leading whitespaces");
	return (false);
}

/**
 * @brief Skips empty lines in the file content.
 *
 * @param lines Array of file lines.
 * @param start_row The index to start checking from.
 * @return The index of the first non-empty line.
 */
size_t	skip_empty_lines(char **lines, size_t start_row)
{
	size_t	map_start;

	map_start = start_row;
	while (lines[map_start] && is_empty_line(lines[map_start]))
		map_start++;
	return (map_start);
}
