/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:26:09 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/25 20:19:28 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

/**
 * @brief Main entry point of the Cub3D program.
 *
 * Initializes data, parses arguments and map file, and starts the game loop.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return 0 on success, 1 on error.
 */
int	main(int argc, char **argv)
{
	t_map_data	map_data;

	log_msg(DEBUG, __FILE__, __LINE__, "executing cub3d");
	ft_bzero(&map_data, sizeof(t_map_data));
	if (parse(argc, argv, &map_data))
		return (main_cleanup(&map_data), 1);
	return (main_cleanup(&map_data), 0);
}
