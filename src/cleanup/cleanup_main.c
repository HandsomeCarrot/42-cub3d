/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:55:19 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/23 18:53:34 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cleanup.h"

/**
 * @brief Frees all allocated memory within the map data structure.
 *
 * @param data Pointer to the map data structure to be freed.
 */
static void	free_map_data(t_map_data *data)
{
	log_msg(DEBUG, __FILE__, __LINE__, "cleaning map data");
	if (data->map.layout)
		free_string_array(&data->map.layout);
	if (data->images.north_wall)
		free(data->images.north_wall);
	if (data->images.east_wall)
		free(data->images.east_wall);
	if (data->images.south_wall)
		free(data->images.south_wall);
	if (data->images.west_wall)
		free(data->images.west_wall);
}

/**
 * @brief Performs the main cleanup of the program resources.
 *
 * Frees the map data.
 *
 * @param data Pointer to the main data structure.
 */
void	main_cleanup(t_map_data *data)
{
	log_msg(DEBUG, __FILE__, __LINE__, "cleaning data");
	if (data)
	{
		free_map_data(data);
	}
}
