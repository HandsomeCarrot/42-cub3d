/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 17:12:48 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/22 13:13:45 by vpoka            ###   ########.fr       */
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

/**
 * @brief Skips whitespace characters in a string.
 *
 * @param str The string to scan.
 * @return The number of whitespace characters skipped.
 */
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
