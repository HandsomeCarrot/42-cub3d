/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 17:07:29 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/23 18:51:01 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/parsing.h"

/**
 * @brief Iterates over file data to extract texture information.
 *
 * Skips empty lines and extracts data for NO, EA, SO, WE, F, C.
 * Stops when map layout starts or end of file is reached.
 *
 * @param file_data The content of the map file.
 * @param ids Array of map identifiers.
 * @param data Main data structure to store extracted info.
 * @param line Pointer to current line index (updated).
 * @return 0 on success, 1 on error.
 */
static int	process_texture_lines(char **file_data, t_map_id *ids,
		t_map_data *data, int *line)
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

/**
 * @brief Extracts all texture and color data from the map file.
 *
 * Initializes identifiers, processes lines, and updates the row index
 * to point to the start of the map layout.
 *
 * @param file_data The content of the map file.
 * @param data Main data structure.
 * @param row Pointer to store the index where map layout starts.
 * @return 0 on success, 1 on error.
 */
static int	extract_texture_data(char **file_data, t_map_data *data,
		size_t *row)
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
 * @brief Orchestrates the extraction of all data from the file content.
 *
 * Extracts textures, colors, and the map layout. Also checks for
 * hanging lines after the map.
 *
 * @param file_data The content of the map file.
 * @param data Main data structure.
 * @return 0 on success, 1 on error.
 */
static int	extract_file_data(char **file_data, t_map_data *data)
{
	size_t	row;

	log_msg(DEBUG, __FILE__, __LINE__, "extracting map file data");
	if (!file_data || !data)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	if (extract_texture_data(file_data, data, &row))
		return (1);
	if (extract_map_layout(file_data, &row, &(data->map)))
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
int	parse_map_file(char *file, t_map_data *data)
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
