/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:55:19 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/11 13:38:22 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cleanup.h"

static void	free_map_data(t_map_data data)
{
	log_msg(DEBUG, __FILE__, __LINE__, "cleaning map data");
	if (data.map)
		free_string_array(&data.map);
	if (data.north_wall_image)
		free(data.north_wall_image);
	if (data.east_wall_image)
		free(data.east_wall_image);
	if (data.south_wall_image)
		free(data.south_wall_image);
	if (data.west_wall_image)
		free(data.west_wall_image);
}

void	main_cleanup(t_data *data)
{
	log_msg(DEBUG, __FILE__, __LINE__, "cleaning data");
	if (data)
	{
		free_map_data(data->map_data);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		free(data);
	}
}
