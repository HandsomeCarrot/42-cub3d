/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:39:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/26 13:25:24 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	is_whitespace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

static const t_map_identifiers	*get_map_identifiers(void)
{
	const t_map_identifiers	ids[] = {
		{IMAGE, "NO", 2, false},
		{IMAGE, "EA", 2, false},
		{IMAGE, "SO", 2, false},
		{IMAGE, "WE", 2, false},
		{COLOR, "F", 1, false},
		{COLOR, "C", 1, false},
		{NULL, NONE, 0, false}
	};

	return (ids);
}

static t_map_data_type	is_empty(char *line, int row)
{
	char			*trimmed;
	int				log_fd;
	t_map_data_type	return_code;

	if (!line)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), INVALID);
	if (ft_isprint(*line))
		return (IMAGE);
	trimmed = ft_strtrim(line, WHITESPACE);
	if (!trimmed)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_ALLOC_FAIL), INVALID);
	return_code = NONE;
	if (*trimmed != '\0')
	{
		log_fd = log_start(ERROR, __FILE__, __LINE__);
		if (log_fd >= 0)
		{
			ft_putstr_fd("in line ", log_fd);
			ft_putnbr_fd(row, log_fd);
			ft_putendl_fd(": whitespace in front of data ID", log_fd);
		}
		return_code = INVALID;
	}
	free(trimmed);
	return (return_code);
}

static t_map_data_type	get_map_data_type(char *line, int row)
{
	const t_map_identifiers	*ids;
	t_map_data_type			empty;
	int						id_pos;

	if (!line)
		return (log_msg(DEBUG, __FILE__, __LINE__, LOG_INVALID_PARAM), NONE);
	empty = is_empty(line, row);
	if (empty <= NONE)
		return (empty);
	ids = get_map_identifiers();
	id_pos = 0;
	while (ids && ids[id_pos].id)
	{
		if (ft_strncmp(line, ids[id_pos].id, ids[id_pos].id_len) == 0
			&& is_whitespace(line[ids[id_pos].id_len]))
			return (ids[id_pos].type);
		id_pos++;
	}
}

/**
 * saves the data on the current line, if there is some and it is valid
 * 
 * @return 0 on success, other on error
 */
static int	save_line_data(char *line, int row, t_data *data)
{
	//t_map_data_type	data_type;

	(void)line;
	(void)data;
	(void)row;
	//data_type = get_map_data_type(line, row);
	//if (data_type == IMAGE)
	//	return (save_image(line, data));
	//else if (data_type == COLOR)
	//	return (save_color(line, data));
	//else if (data_type == INVALID)
	//	return (1);
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
	int	line;

	log_msg(DEBUG, __FILE__, __LINE__, "extracting map file information");
	if (!file_data || !data)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	line = 0;
	while (file_data[line] /*&& !is_map(file_data[line])*/)
	{
		if (save_line_data(file_data[line], line, data))
			return (1);
		//skip lines with no data
		//loop until first part of map is reached
		line++;
	}
	//check if all necessary data was extracted and there is no more/less data then needed
	return (0);
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
	//extract map & player info (posX posY W/N/E/S)
	//check for invalid hanging data
	//convert xpm's to mlx images and extract data
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

	(void)data;
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
