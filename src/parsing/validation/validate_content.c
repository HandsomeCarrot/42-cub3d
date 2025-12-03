/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:23:22 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/23 18:53:28 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/parsing/parsing.h"

/**
 * @brief Validates that no extra content follows the image path
 *
 * @param line The configuration line
 * @param data_id Map identifier metadata
 * @param skipped Number of characters already processed
 * @param row Line number for error reporting
 * @return true if valid, false if extra content detected
 */
bool	has_trailing_content(char *line, int row)
{
	size_t	skipped;

	skipped = skip_whitespace(line);
	if (line[skipped] != 0)
	{
		printf("'%s'\n + %ld = '%s'\n", line, skipped, line + skipped);
		log_line_error(row, "extra content found after map configuration data",
			__FILE__, __LINE__);
		return (true);
	}
	return (false);
}

/**
 * @brief Checks for non-empty lines after the map layout.
 *
 * @param lines Array of file lines.
 * @param row The index where the map layout ended.
 * @return 0 on success (no hanging lines), 1 on error.
 */
int	check_hanging_lines(char **lines, size_t row)
{
	if (!lines)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	while (lines[row])
	{
		if (!is_empty_line(lines[row]))
		{
			log_line_error(row + 1, "found non-empty line after map layout",
				__FILE__, __LINE__);
			return (1);
		}
		row++;
	}
	return (0);
}
