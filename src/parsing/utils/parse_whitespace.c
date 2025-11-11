/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_whitespace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 19:28:02 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/11 19:30:21 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief checks if 'c' is a whitespace character
 *
 * @param c character to compare whitespace characters to
 * @return true if a whitespace character, false otherwise
 */
bool	is_whitespace(char c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (true);
	return (false);
}

size_t	skip_whitespace(const char *str)
{
	size_t	skipped;

	if (!str)
		return (log_msg(WARNING, __FILE__, __LINE__, LOG_INVALID_PARAM), 0);
	skipped = 0;
	while (is_whitespace(str[skipped]))
		skipped++;
	return (skipped);
}

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
 * returns true if the first character of 'line' is a whitespace character,
 * false otherwise
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
