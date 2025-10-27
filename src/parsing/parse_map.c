/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:39:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/27 22:42:57 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief checks if 'c' is a whitespace character
 *
 * @param c character to compare whitespace characters to
 * @return true if a whitespace character, false otherwise
 */
static bool	is_whitespace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

/**
 * @return table with defined identifiers accepted in map
 */
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
	ids[0] = (t_map_id){IMAGE, false, "NO", 2, "North wall"};
	ids[1] = (t_map_id){IMAGE, false, "EA", 2, "East wall"};
	ids[2] = (t_map_id){IMAGE, false, "SO", 2, "South wall"};
	ids[3] = (t_map_id){IMAGE, false, "WE", 2, "West wall"};
	ids[4] = (t_map_id){COLOR, false, "C", 1, "Ceiling"};
	ids[5] = (t_map_id){COLOR, false, "F", 1, "Floor"};
	return (ids);
}

/**
 * @brief checks if the 'line' only consists of whitespace characters
 *
 * @param line string to check
 *
 * @return true if it is empty, false otherwise
 */
static bool	is_empty(char *line)
{
	char	*trimmed;
	bool	empty;

	if (!line)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), false);
	log_msg(DEBUG, __FILE__, __LINE__, "checking for empty line");
	trimmed = ft_strtrim(line, WHITESPACE);
	if (!trimmed)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_ALLOC_FAIL), false);
	empty = trimmed[0] == 0;
	free(trimmed);
	return (empty);
}

/**
 * returns true if the first character of 'line' is a whitespace character,
 * false otherwise
 */
static bool	has_leading_whitespace(char *line, int row)
{
	if (!line)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), true);
	log_msg(DEBUG, __FILE__, __LINE__, "checking for leading whitespaces");
	if (is_whitespace(line[0]))
	{
		log_line_error(row + 1, "leading whitespace before map data",
			__FILE__, __LINE__);
		return (true);
	}
	return (false);
}

/**
 * checks if this identifier was already found
 */
static bool	is_duplicate_id(t_map_id data_id, int row)
{
	int	log_fd;

	if (!data_id.found)
		return (false);
	log_fd = log_start(ERROR, __FILE__, __LINE__);
	if (log_fd >= 0)
	{
		ft_putstr_fd("in map on line ", log_fd);
		ft_putnbr_fd(row, log_fd);
		ft_putstr_fd(": duplicate declaration of '", log_fd);
		ft_putstr_fd((char *)data_id.id, log_fd);
		ft_putendl_fd("'", log_fd);
	}
	return (true);
}

/**
 * checks if 'line' starts with the same characters as 'data_id'
 */
static bool has_same_id(char *line, t_map_id data_id)
{
	if (!line)
		return (log_msg(WARNING, __FILE__, __LINE__, LOG_ALLOC_FAIL), false);
	if (!ft_strncmp(line, data_id.id, data_id.id_len) && is_whitespace(line[data_id.id_len]))
		return (true);
	return (false);
}

/**
 * returns a pointer to data_id entry that was found, NULL on error
 */
static t_map_id	*get_map_data_type(char *line, int row, t_map_id *ids)
{
	int	id_pos;

	if (!line || !ids)
		return (log_msg(DEBUG, __FILE__, __LINE__, LOG_INVALID_PARAM), NULL);
	log_msg(DEBUG, __FILE__, __LINE__, "determining map data type");
	id_pos = 0;
	while (ids && ids[id_pos].id)
	{
		if (has_same_id(line, ids[id_pos]))
		{
			if (is_duplicate_id(ids[id_pos], row))
				return (NULL);
			ids[id_pos].found = true;
			return (&ids[id_pos]);
		}
		id_pos++;
	}
	log_line_error(row + 1, "unknown map data identifier", __FILE__, __LINE__);
	return (NULL);
}

/**
 * prints a log message
 */
static void	log_id_processing(t_map_id *data_id, char *src_file, int src_line)
{
	int	log_fd;

	if (!data_id || !src_file)
	{
		log_msg(WARNING, __FILE__, __LINE__, LOG_INVALID_PARAM);
		return ;
	}
	log_fd = log_start(INFO, src_file, src_line);
	if (log_fd < 0)
		return ;
	ft_putstr_fd("processing ", log_fd);
	if (data_id->id_description)
	{
		ft_putstr_fd((char *)data_id->id_description, log_fd);
		ft_putchar_fd(' ', log_fd);
	}
	if (data_id->type == IMAGE)
		ft_putstr_fd("image", log_fd);
	else if (data_id->type == COLOR)
		ft_putstr_fd("color", log_fd);
	ft_putchar_fd('\n', log_fd);
}

/**
 * returns amount of characters it skipped which consists of
 * - skipped whitespace characters
 * - characters until next whitespace/null character
 */
static size_t	get_next_char_block(char **save, char *str)
{
	size_t	spaces;
	size_t	str_len;

	if (!save || !str)
		return (log_msg(WARNING, __FILE__, __LINE__, LOG_INVALID_PARAM), 0);
	spaces = 0;
	while (is_whitespace(str[spaces]))
		spaces++;
	str_len = 0;
	while(str[spaces + str_len] && !is_whitespace(str[spaces + str_len]))
		str_len++;
	if (str_len == 0)
		return (0);
	*save = ft_substr(str, spaces, str_len);
	if (!*save)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_ALLOC_FAIL), 0);
	return (spaces + str_len);
}

/**
 * @return 0 on success, other on error
 */
static int	save_image(char *line, int row, t_map_id *data_id, t_data *data)
{
	char	*img_path;
	size_t	skipped;

	if (!line || !data_id || !data)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	log_id_processing(data_id, __FILE__, __LINE__);
	skipped = get_next_char_block(&img_path, line + data_id->id_len);
	if (skipped == 0 || (!is_whitespace(line[data_id->id_len + skipped])))
	{
		log_line_error(row + 1, "no image path given", __FILE__, __LINE__);
		return (1);
	}
	free(img_path);
	return (0);
}

/**
 * @return 0 on success, other on error
 */
static int	save_color(char *line, t_map_id *data_id, t_data *data)
{
	if (!line || !data_id || !data)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	log_id_processing(data_id, __FILE__, __LINE__);
	return (0);
}

/**
 * saves the data on the current line, if there is some and it is valid
 *
 * @return 0 on success, other on error
 */
static int	save_line_data(char *line, int row, t_map_id *ids, t_data *data)
{
	t_map_id	*data_id;

	if (!line || !ids || !data)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	log_msg(DEBUG, __FILE__, __LINE__, "processing line");
	if (is_empty(line))
		return (0);
	if (has_leading_whitespace(line, row))
		return (1);
	data_id = get_map_data_type(line, row, ids);
	if (!data_id)
		return (1);
	if (data_id->type == IMAGE)
		return (save_image(line, row, data_id, data));
	else if (data_id->type == COLOR)
		return (save_color(line, data_id, data));
	log_msg(ERROR, __FILE__, __LINE__, "data type not recognized");
	return (1);
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
