/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file_reader.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 17:07:29 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/21 19:20:07 by vpoka            ###   ########.fr       */
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
static int	process_texture_lines(char **file_data, t_map_id *ids,
		t_data *data, int *line)
{
	if (!file_data || !ids || !data || !line)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	while (file_data[++(*line)] && !all_ids_found(ids))
	{
		if (is_empty_line(file_data[*line]))
			continue ;
		if (save_line_data(file_data[*line], *line + 1, ids, data))
			return (1);
	}
	return (0);
}

static int	extract_texture_data(char **file_data, t_data *data, size_t *row)
{
	t_map_id	*ids;
	int			line;

	log_msg(DEBUG, __FILE__, __LINE__, "extracting texture data from map file");
	if (!file_data || !data || !row)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	ids = get_map_identifiers();
	if (!ids)
		return (1);
	line = -1;
	if (!file_data[0])
	{
		log_missing_ids(ids);
		free(ids);
		return (1);
	}
	if (process_texture_lines(file_data, ids, data, &line))
	{
		free(ids);
		return (1);
	}
	*row = (size_t)line;
	free(ids);
	log_msg(INFO, __FILE__, __LINE__, "extracted all necessary texture data");
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

/**
 * @brief Parses map data from a specified map file.
 *
 * This function validates the file extension, opens the file for
 * reading, reads all lines into memory, and prepares for parsing the
 * map data. Currently, the actual parsing logic is not implemented.
 *
 * @param file The path to the map file with a .cub extension.
 * @param data A pointer to the data structure where parsed information
 *             should be stored (currently unused).
 *
 * @return 0 on successful parsing, 1 on error (invalid extension, file
 *         open failure, or reading failure).
 *
 * @note The function logs informational messages and ensures the file
 *       is properly closed after reading.
 */
int	parse_map_file(char *file, t_data *data)
{
	char	**lines;
	int		ret;

	log_msg(INFO, __FILE__, __LINE__, "parsing map file");
	if (correct_file_extension(file, ".cub"))
		return (1);
	lines = read_file(file);
	if (!lines)
		return (1);
	ret = extract_file_data(lines, data);
	free_string_array(&lines);
	return (ret);
}
