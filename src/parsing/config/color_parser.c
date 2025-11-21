/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:41:51 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/21 18:23:45 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Parses and validates a single color channel value from the string
 *
 * @param colors_string Pointer to the string containing color data
 * @param color_channel Pointer to store the parsed color value
 * @return int 0 on success, 1 on failure
 */
static int	parse_color_channel(char **colors_string, int *color_channel,
		int row)
{
	int	num;

	if (!colors_string || !*colors_string || !color_channel)
		return (log_msg(ERROR, __FILE__, __LINE__,
				"Invalid parameters for color parsing"), 1);
	log_msg(DEBUG, __FILE__, __LINE__, "Parsing color channel value");
	if (!ft_isdigit((*colors_string)[0]))
		return (log_msg(ERROR, __FILE__, __LINE__,
				"Invalid character in color value - expected digit"), 1);
	num = ft_atoi(*colors_string);
	if (num < 0 || num > 255)
	{
		log_line_error(row,
			"Color value out of range: must be between 0 and 255",
			__FILE__, __LINE__);
		return (1);
	}
	*color_channel = num;
	while (ft_isdigit((*colors_string)[0]))
		(*colors_string)++;
	log_msg(DEBUG, __FILE__, __LINE__,
		"Successfully parsed color channel value");
	return (0);
}

/**
 * @brief Validates and processes the separator between color channels
 *
 * @param colors_string Pointer to the string containing color data
 * @return int 0 on success, 1 on failure
 */
static int	process_separator(char **colors_string)
{
	if (!colors_string || !*colors_string)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	*colors_string += skip_whitespace(*colors_string);
	if ((*colors_string)[0] != ',')
		return (log_msg(ERROR, __FILE__, __LINE__, "invalid char detected"), 1);
	(*colors_string)++;
	*colors_string += skip_whitespace(*colors_string);
	return (0);
}

/**
 * @brief Assigns the final color value to the appropriate ceiling or floor
 *
 * @param data_id Map identifier metadata
 * @param colors Colors structure to store the result
 * @param final_color The computed color value
 * @return int 0 on success, 1 on failure
 */
static int	assign_final_color(t_map_id *data_id, t_colors *colors,
		int final_color)
{
	if (!data_id || !colors)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	if (ft_strncmp(data_id->id, "C", data_id->id_len) == 0)
		colors->ceiling = final_color;
	else if (ft_strncmp(data_id->id, "F", data_id->id_len) == 0)
		colors->floor = final_color;
	else
		return (log_msg(ERROR, __FILE__, __LINE__,
				"invalid color identifier"), 1);
	log_found_color(final_color, __FILE__, __LINE__);
	return (0);
}

/**
 * @brief Processes RGB color channels sequentially
 *
 * @param colors_string Pointer to the string containing color data
 * @param final_color Pointer to store the computed color value
 * @return int 0 on success, 1 on failure
 */
static int	process_rgb_channels(char **colors_string, int *final_color,
		int row)
{
	int	color_channel;

	if (!colors_string || !*colors_string || !final_color)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	if (parse_color_channel(colors_string, &color_channel, row))
		return (1);
	*final_color = set_color_channel(0, RED_CH, color_channel);
	if (process_separator(colors_string))
		return (1);
	if (parse_color_channel(colors_string, &color_channel, row))
		return (1);
	*final_color = set_color_channel(*final_color, GREEN_CH, color_channel);
	if (process_separator(colors_string))
		return (1);
	if (parse_color_channel(colors_string, &color_channel, row))
		return (1);
	*final_color = set_color_channel(*final_color, BLUE_CH, color_channel);
	return (0);
}

/**
 * @brief Saves color configuration from map file line
 *
 * Parses RGB color values from configuration line and stores them
 * in the appropriate ceiling or floor color field.
 *
 * @param line The configuration line containing color data
 * @param data_id Map identifier metadata
 * @param colors Colors structure to store the result
 * @return int 0 on success, 1 on error
 */
int	save_color(char *line, int row, t_map_id *data_id, t_colors *colors)
{
	char	*colors_string;
	int		final_color;

	if (!line || !data_id || !colors)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	log_id_processing(data_id, __FILE__, __LINE__);
	colors_string = line + data_id->id_len;
	colors_string += skip_whitespace(colors_string);
	if (process_rgb_channels(&colors_string, &final_color, row))
		return (1);
	if (has_trailing_content(colors_string, 0))
		return (1);
	if (assign_final_color(data_id, colors, final_color))
		return (1);
	return (0);
}
