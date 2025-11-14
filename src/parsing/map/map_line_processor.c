/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_line_processor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:39:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/14 17:49:29 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * returns amount of characters it skipped which consists of
 * - skipped whitespace characters
 * - characters until next whitespace/null character
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
 * @return true, or false
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
			log_line_error(row, "invalid character in map", __FILE__, __LINE__);
			return (false);
		}
		pos++;
	}
	if (pos > map->width)
		map->width = pos;
	return (true);
}

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
