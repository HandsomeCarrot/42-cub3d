/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_identifiers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:34:35 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/21 17:44:18 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * checks if 'line' starts with the same characters as 'data_id'
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
 * returns a pointer to data_id entry that was found, NULL on error
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
 * @brief Logs which texture identifiers are missing
 *
 * @param ids Array of texture identifiers to check
 */
void	log_missing_ids(t_map_id *ids)
{
	int	id_pos;
	int	log_fd;

	if (!ids)
		return ;
	log_fd = log_start(ERROR, __FILE__, __LINE__);
	if (log_fd < 0)
		return ;
	ft_putstr_fd("missing texture identifier(s): ", log_fd);
	id_pos = 0;
	while (ids[id_pos].id)
	{
		if (!ids[id_pos].found)
		{
			ft_putstr_fd("'", log_fd);
			ft_putstr_fd((char *)ids[id_pos].id, log_fd);
			ft_putstr_fd("' ", log_fd);
		}
		id_pos++;
	}
	ft_putendl_fd("", log_fd);
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
 * @return table with defined identifiers accepted in map
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
