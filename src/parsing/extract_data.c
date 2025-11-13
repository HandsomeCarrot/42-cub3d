/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 16:12:14 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/13 17:53:09 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * Iterates over the file data and checks each line for info.
 * If the line is empty it gets skipped.
 * If there is some info (NO, EA, SO, WE, F, C)
 * it will get extracted and saved.
 * Stops the loop when it reaches the first line of the map,
 * or the end of the data.
 *
 * should also check if all info was provided
 *
 * @return 0 on success, other on error
 */
static int	extract_texture_data(char **file_data, t_data *data, size_t *row)
{
	t_map_id	*ids;
	int			line;

	log_msg(DEBUG, __FILE__, __LINE__, "extracting texture data from map file");
	if (!file_data || !data)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	ids = get_map_identifiers();
	if (!ids)
		return (1);
	line = -1;
	while (file_data[++line] && !all_ids_found(ids))
	{
		if (is_empty_line(file_data[line]))
			continue ;
		if (!save_line_data(file_data[line], line + 1, ids, data))
		{
			free(ids);
			return (1);
		}
	}
	if (row)
		*row = (size_t)line;
	free(ids);
	log_msg(INFO, __FILE__, __LINE__, "extracted all necessary texture data");
	return (0);
}

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
static int	extract_map_layout(char **lines, size_t *row, t_map *map)
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

/**
 * @brief parse and save the data from the file data
 *
 * @return 0 on success, other on error
 */
static int	extract_file_data(char **file_data, t_data *data)
{
	size_t	row;

	log_msg(DEBUG, __FILE__, __LINE__, "extracting map file data");
	if (!file_data || !data)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	if (extract_texture_data(file_data, data, &row))
		return (1);
	if (extract_map_layout(file_data, &row, &(data->map_data.map)))
		return (1);
	if (check_hanging_lines(file_data, row))
		return (1);
	log_msg(DEBUG, __FILE__, __LINE__, "extracted map file data successfully");
	return (0);
}
