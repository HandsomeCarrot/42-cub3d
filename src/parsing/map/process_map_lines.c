/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map_lines.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:39:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/23 18:50:36 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/parsing/parsing.h"

/**
 * @brief Extracts the next block of characters from a string.
 *
 * Skips whitespace and extracts characters until the next whitespace or null.
 *
 * @param save Pointer to store the extracted string.
 * @param str The source string.
 * @return The number of characters processed (skipped + extracted).
 */
size_t	get_next_char_block(char **save, const char *str)
{
	size_t	spaces;
	size_t	str_len;

	if (!save || !str)
		return (log_msg(WARNING, __FILE__, __LINE__, LOG_INVALID_PARAM), 0);
	spaces = skip_whitespace(str);
	str += spaces;
	str_len = 0;
	while (str[str_len] && !is_whitespace(str[str_len]))
		str_len++;
	if (str_len == 0)
		return (0);
	*save = ft_substr(str, 0, str_len);
	if (!*save)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_ALLOC_FAIL), 0);
	return (spaces + str_len);
}

/**
 * @brief Validates if a line contains only valid map characters.
 *
 * Updates the map width if the current line is longer.
 *
 * @param line The line to validate.
 * @param row The line number for error reporting.
 * @param map Pointer to map structure.
 * @return true if valid, false otherwise.
 */
bool	is_valid_layout_line(const char *line, size_t row, t_map *map)
{
	int	pos;

	if (!line || !map)
		return (log_msg(WARNING, __FILE__, __LINE__, LOG_INVALID_PARAM), false);
	pos = 0;
	while (line[pos] && line[pos] != '\n')
	{
		if (!ft_strchr(MAP_LAYOUT_CHARACTERS, line[pos]))
		{
			log_invalid_map_line(row, line, pos);
			return (false);
		}
		pos++;
	}
	if (pos > map->width)
		map->width = pos;
	return (true);
}

/**
 * @brief Creates a new map line padded with spaces to match map width.
 *
 * @param old_line The original map line.
 * @param map Pointer to map structure containing width.
 * @return Pointer to the new padded line, or NULL on failure.
 */
char	*modified_map_line(char *old_line, t_map *map)
{
	char	*new_line;
	int		pos;

	if (!old_line || !map)
		return (log_msg(WARNING, __FILE__, __LINE__, LOG_INVALID_PARAM), NULL);
	log_msg(DEBUG, __FILE__, __LINE__, "creating new map line");
	new_line = log_calloc(map->width + 1, sizeof(char), __FILE__, __LINE__);
	if (!new_line)
		return (NULL);
	pos = 0;
	while (pos < map->width && old_line[pos] && old_line[pos] != '\n')
	{
		new_line[pos] = old_line[pos];
		pos++;
	}
	while (pos < map->width)
	{
		new_line[pos] = ' ';
		pos++;
	}
	return (new_line);
}
