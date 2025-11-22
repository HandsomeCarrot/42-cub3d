/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:34:35 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/22 13:12:49 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Checks if 'line' starts with the same characters as 'data_id'.
 *
 * @param line The line to check.
 * @param data_id The map identifier to compare against.
 * @return true if match found, false otherwise.
 */
static bool	has_same_id(char *line, t_map_id data_id)
{
	if (!line)
		return (log_msg(WARNING, __FILE__, __LINE__, LOG_ALLOC_FAIL), false);
	if (!ft_strncmp(line, data_id.id, data_id.id_len)
		&& is_whitespace(line[data_id.id_len]))
		return (true);
	return (false);
}

/**
 * @brief Checks if this identifier was already found.
 *
 * Logs an error if a duplicate is found.
 *
 * @param data_id The map identifier to check.
 * @param row The current line number in the map file.
 * @return true if duplicate found, false otherwise.
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
 * @brief Identifies the type of map data in the given line.
 *
 * @param line The line to analyze.
 * @param row The current line number in the map file.
 * @param ids Array of valid map identifiers.
 * @return Pointer to the found map identifier, or NULL if not found or error.
 */
t_map_id	*get_map_data_type(char *line, int row, t_map_id *ids)
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
	log_missing_ids(ids);
	return (NULL);
}

/**
 * @brief Checks if all required texture identifiers have been found
 *
 * @param ids Array of texture identifiers to check
 * @return true if all identifiers have been found, false otherwise
 */
bool	all_ids_found(t_map_id *ids)
{
	int	id_pos;

	if (!ids)
		return (log_msg(WARNING, __FILE__, __LINE__, LOG_INVALID_PARAM), false);
	id_pos = 0;
	while (ids[id_pos].id)
	{
		if (!ids[id_pos].found)
			return (false);
		id_pos++;
	}
	return (true);
}

/**
 * @brief Creates a table of defined identifiers accepted in the map.
 *
 * Allocates and initializes the array of valid map identifiers
 * (NO, EA, SO, WE, F, C).
 *
 * @return Pointer to the array of map identifiers, or NULL on failure.
 */
t_map_id	*get_map_identifiers(void)
{
	t_map_id	*ids;
	int			id_count;

	log_msg(DEBUG, __FILE__, __LINE__,
		"creating map texture identifier table (NO, EA, SO, WE, F, C)");
	id_count = 6;
	ids = log_calloc(id_count + 1, sizeof(t_map_id), __FILE__, __LINE__);
	if (!ids)
		return (NULL);
	ids[0] = (t_map_id){T_IMAGE, false, "NO", 2};
	ids[1] = (t_map_id){T_IMAGE, false, "EA", 2};
	ids[2] = (t_map_id){T_IMAGE, false, "SO", 2};
	ids[3] = (t_map_id){T_IMAGE, false, "WE", 2};
	ids[4] = (t_map_id){T_COLOR, false, "C", 1};
	ids[5] = (t_map_id){T_COLOR, false, "F", 1};
	return (ids);
}
