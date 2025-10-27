/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:39:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/27 17:52:49 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	is_whitespace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

static t_map_id	*get_map_identifiers(void)
{
	t_map_id	*ids;
	int			id_count;

	log_msg(DEBUG, __FILE__, __LINE__,
		"creating map identifier table (NO, EA, SO, WE, F, C)");
	id_count = 6;
	ids = log_calloc(id_count + 1, sizeof(t_map_id), __FILE__, __LINE__);
	if (!ids)
		return (NULL);
	ids[0] = (t_map_id){IMAGE, "NO", 2, false};
	ids[1] = (t_map_id){IMAGE, "EA", 2, false};
	ids[2] = (t_map_id){IMAGE, "SO", 2, false};
	ids[3] = (t_map_id){IMAGE, "WE", 2, false};
	ids[4] = (t_map_id){COLOR, "F", 1, false};
	ids[5] = (t_map_id){COLOR, "C", 1, false};
	return (ids);
}

static t_map_data_type	is_empty(char *line, int row)
{
	char			*trimmed;
	t_map_data_type	return_code;

	if (!line)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), INVALID);
	log_msg(DEBUG, __FILE__, __LINE__, "validating line data");
	if (!is_whitespace(*line))
		return (IMAGE);
	trimmed = ft_strtrim(line, WHITESPACE);
	if (!trimmed)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_ALLOC_FAIL), INVALID);
	return_code = NONE;
	if (trimmed[0] != 0)
	{
		log_line_error(row + 1, "leading whitespace before map data",
			__FILE__, __LINE__);
		return_code = INVALID;
	}
	free(trimmed);
	return (return_code);
}

static t_map_data_type	get_map_data_type(char *line, int row, t_map_id *ids)
{
	t_map_data_type	empty;
	int				id_pos;
	int				log_fd;

	if (!line)
		return (log_msg(DEBUG, __FILE__, __LINE__, LOG_INVALID_PARAM), NONE);
	log_msg(DEBUG, __FILE__, __LINE__, "determining map data type");
	empty = is_empty(line, row);
	if (empty == INVALID || empty == NONE)
		return (empty);
	id_pos = 0;
	while (ids && ids[id_pos].id)
	{
		if (ft_strncmp(line, ids[id_pos].id, ids[id_pos].id_len) == 0
			&& is_whitespace(line[ids[id_pos].id_len]))
		{
			if (ids[id_pos].found)
			{
				log_fd = log_start(ERROR, __FILE__, __LINE__);
				if (log_fd >= 0)
				{
					ft_putstr_fd("in map on line ", log_fd);
					ft_putnbr_fd(row, log_fd);
					ft_putstr_fd(": duplicate declaration of '", log_fd);
					ft_putstr_fd((char *)ids[id_pos].id, log_fd);
					ft_putendl_fd("'", log_fd);
				}
				return (INVALID);
			}
			ids[id_pos].found = true;
			return (ids[id_pos].type);
		}
		id_pos++;
	}
	log_line_error(row + 1, "unknown map data identifier", __FILE__, __LINE__);
	return (INVALID);
}

/**
 * @return 0 on success, other on error
 */
static int	save_image(char *line, t_data *data)
{
	if (!line || !data)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	log_msg(INFO, __FILE__, __LINE__, "processing image data");
	return (0);
}

/**
 * @return 0 on success, other on error
 */
static int	save_color(char *line, t_data *data)
{
	if (!line || !data)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	log_msg(INFO, __FILE__, __LINE__, "processing color data");
	return (0);
}

/**
 * saves the data on the current line, if there is some and it is valid
 *
 * @return 0 on success, other on error
 */
static int	save_line_data(char *line, int row, t_map_id *ids, t_data *data)
{
	t_map_data_type	data_type;

	if (!line || !ids || !data)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	log_msg(DEBUG, __FILE__, __LINE__, "processing line");
	data_type = get_map_data_type(line, row, ids);
	if (data_type == IMAGE)
		return (save_image(line, data));
	else if (data_type == COLOR)
		return (save_color(line, data));
	else if (data_type == INVALID)
		return (1);
	return (0);
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
static int	extract_texture_data(char **file_data, t_data *data)
{
	t_map_id	*ids;
	int			line;

	log_msg(DEBUG, __FILE__, __LINE__, "extracting texture data from map file");
	if (!file_data || !data)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	ids = get_map_identifiers();
	if (!ids)
		return (1);
	line = 0;
	while (file_data[line] /*&& !is_map(file_data[line])*/)
	{
		if (save_line_data(file_data[line], line, ids, data))
			return (free(ids), 1);
		// skip lines with no data
		// loop until first part of map is reached
		line++;
	}
	// check if all necessary data was extracted and there is no more/less data then needed
	return (free(ids), 0);
}

/**
 * @brief parse and save the data from the file data
 *
 * @return 0 on success, other on error
 */
static int	parse_file_data(char **file_data, t_data *data)
{
	log_msg(DEBUG, __FILE__, __LINE__, "parsing map file data");
	if (!file_data || !data)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	if (extract_texture_data(file_data, data))
		return (1);
	// extract map & player info (posX posY W/N/E/S)
	// check for invalid hanging data
	// convert xpm's to mlx images and extract data
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
	ret = parse_file_data(lines, data);
	free_string_array(&lines, __FILE__, __LINE__);
	return (ret);
}
