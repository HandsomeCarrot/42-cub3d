/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 17:10:41 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/23 18:50:56 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/parsing/parsing.h"

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
 * @return 0 on success, other on error
 */
static int	call_save_function(t_map_id *data_id, char *line, int row,
		t_map_data *data)
{
	if (!data_id || !line || !data)
	{
		log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM);
		return (1);
	}
	if (data_id->type == T_IMAGE)
		return (save_image(line, row, data_id, data));
	else if (data_id->type == T_COLOR)
		return (save_color(line, row, data_id, &data->colors));
	log_msg(ERROR, __FILE__, __LINE__, "data type not recognized");
	return (1);
}

/**
 * @brief Processes and saves data from a single line of the map file.
 *
 * Identifies the data type (texture or color) and calls the appropriate
 * save function.
 *
 * @param line The line to process.
 * @param row The line number for error reporting.
 * @param ids Array of map identifiers.
 * @param data Main data structure.
 * @return 0 on success, 1 on error.
 */
int	save_line_data(char *line, int row, t_map_id *ids, t_map_data *data)
{
	t_map_id	*data_id;

	if (!line || !ids || !data)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	log_msg(DEBUG, __FILE__, __LINE__, "processing line");
	if (has_leading_whitespace(line, row))
		return (0);
	data_id = get_map_data_type(line, row, ids);
	if (!data_id)
		return (1);
	return (call_save_function(data_id, line, row, data));
}
