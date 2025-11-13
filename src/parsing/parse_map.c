/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:39:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/13 13:43:13 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * returns amount of characters it skipped which consists of
 * - skipped whitespace characters
 * - characters until next whitespace/null character
 */
static size_t	get_next_char_block(char **save, const char *str)
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
 * @brief Validates that no extra content follows the image path
 *
 * @param line The configuration line
 * @param data_id Map identifier metadata
 * @param skipped Number of characters already processed
 * @param row Line number for error reporting
 * @return true if valid, false if extra content detected
 */
static bool	validate_trailing_content(char *line, int row)
{
	size_t	skipped;

	skipped = skip_whitespace(line);
	if (line[skipped] != 0)
	{
		printf("'%s'\n + %ld = '%s'\n", line, skipped, line + skipped);
		log_line_error(row, "extra content found after map configuration data",
			__FILE__, __LINE__);
		return (false);
	}
	return (true);
}

/**
 * @brief Selects and calls the appropriate save function based on data type
 *
 * Routes to save_image() for IMAGE type, save_color() for COLOR type,
 * and handles unrecognized types with error logging.
 *
 * @param data_id Map identifier metadata
 * @param line The configuration line
 * @param row Line number for error reporting
 * @param data Main data structure to store parsed data
 * @return 0 on error, other on success
 */
static int	call_save_function(t_map_id *data_id, char *line, int row,
		t_data *data)
{
	if (!data_id || !line || !data)
	{
		log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM);
		return (0);
	}
	if (data_id->type == T_IMAGE)
		return (save_image(line, row, data_id, data));
	else if (data_id->type == T_COLOR)
		return (save_color(line, data_id, &data->map_data.colors));
	log_msg(ERROR, __FILE__, __LINE__, "data type not recognized");
	return (0);
}

/**
 * saves the data on the current line, if there is some and it is valid
 *
 * @return 0 on error, other on success
 */
static int	save_line_data(char *line, int row, t_map_id *ids, t_data *data)
{
	t_map_id	*data_id;

	if (!line || !ids || !data)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	log_msg(DEBUG, __FILE__, __LINE__, "processing line");
	if (has_leading_whitespace(line, row))
		return (0);
	data_id = get_map_data_type(line, row, ids);
	if (!data_id)
		return (0);
	return (call_save_function(data_id, line, row, data));
}

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
 * @return true, or false
 */
static bool	is_valid_layout_line(const char *line, size_t row, t_map *map)
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

static char	*modified_map_line(char *old_line, t_map *map)
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

/**
 * @return 0 on success, other on fail
 */
static int	extract_map_layout(char **lines, size_t *row, t_map *map)
{
	size_t	map_start;
	size_t	map_height;
	size_t	i;

	if (!lines || !row || !map)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	log_msg(INFO, __FILE__, __LINE__, "getting map layout");
	map_start = *row;
	while (lines[map_start] && is_empty_line(lines[map_start])) //skip empty lines before map lines
		map_start++;
	if (!lines[map_start]) //return error if no more lines are available
		return (1);
	map_height = 0;
	while (lines[map_start + map_height]) //count how many lines the map has
	{
		if (is_empty_line(lines[map_start + map_height]))
			break ;
		if (!is_valid_layout_line(lines[map_start + map_height], map_height + 1, map))
			return (1);
		map_height++;
	}
	*row = map_start + map_height;
	map->layout = log_calloc(map_height + 1, sizeof(char *), __FILE__, __LINE__);
	if (!map->layout)
		return (1);
	map->height = map_height;
	i = 0;
	while(i < map_height && lines[map_start + i]) //save the map layout to a new string array
	{
		map->layout[i] = modified_map_line(lines[map_start + i], map);
		if (!map->layout[i])
			return (1);
		i++;
	}
	log_msg(DEBUG, __FILE__, __LINE__, "map layout extracted");
	return (0);
}

/**
 * @return 0 on success, other on error
 */
static int	check_hanging_lines(char **lines, size_t row)
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
