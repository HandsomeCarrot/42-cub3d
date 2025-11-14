/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_layout_extractor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 16:12:14 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/14 17:48:07 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Count map height and validate each map line.
 * @return map_height on success, SIZE_MAX on error
 */
static size_t	get_map_height(char **lines, size_t map_start, t_map *map)
{
	size_t	map_height;

	map_height = 0;
	while (lines[map_start + map_height])
	{
		if (is_empty_line(lines[map_start + map_height]))
			break ;
		if (!is_valid_layout_line(lines[map_start + map_height],
			map_height + 1, map))
			return (0);
		map_height++;
	}
	if (map_height == 0)
		log_msg(ERROR, __FILE__, __LINE__, "no map layout given");
	return (map_height);
}

/**
 * Allocate memory and populate the map layout with validated lines.
 * @return 0 on success, 1 on error
 */
static int	populate_map_layout(char **lines, size_t map_start, t_map *map)
{
	size_t	i;
	size_t	map_height;

	map_height = map->height;
	map->layout = log_calloc(map_height + 1, sizeof(char *),
		__FILE__, __LINE__);
	if (!map->layout)
		return (1);
	i = 0;
	while (i < map_height && lines[map_start + i])
	{
		map->layout[i] = modified_map_line(lines[map_start + i], map);
		if (!map->layout[i])
			return (1);
		i++;
	}
	return (0);
}

/**
 * @return 0 on success, other on fail
 */
int	extract_map_layout(char **lines, size_t *row, t_map *map)
{
	size_t	map_start;
	size_t	map_height;

	if (!lines || !row || !map)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	log_msg(INFO, __FILE__, __LINE__, "getting map layout");
	map_start = skip_empty_lines(lines, *row);
	map_height = get_map_height(lines, map_start, map);
	if (map_height == 0)
		return (1);
	map->height = map_height;
	*row = map_start + map_height;
	if (populate_map_layout(lines, map_start, map))
		return (1);
	log_msg(DEBUG, __FILE__, __LINE__, "map layout extracted");
	return (0);
}
