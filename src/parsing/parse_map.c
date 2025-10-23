/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:39:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/23 21:29:39 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * saves the data on the current line, if there is some and it is valid
 * 
 * @return 0 on success, other on error
 */
static int	save_line_data(char *line, t_data *data)
{
	//t_map_data_type	data_type;

	(void)line;
	(void)data;
	//data_type = get_map_data_type(line);
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
		return (log_msg(ERROR, __FILE__, __LINE__, INVALID_PARAMETER), 1);
	line = 0;
	while (file_data[line] /*&& !is_map(file_data[line])*/)
	{
		if (save_line_data(file_data[line], data))
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
		return (log_msg(ERROR, __FILE__, __LINE__, INVALID_PARAMETER), 1);
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
