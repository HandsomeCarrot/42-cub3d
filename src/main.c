/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:26:09 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/28 17:51:00 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
	{
		main_cleanup(&map_data);
		return (1);
	}

	t_game		game;

	ft_bzero(&game, sizeof(t_game));
	init_player(&game.player, map_data.player.pos_x, map_data.player.pos_y, map_data.player.orientation);
	game.map = map_data.map.layout;
	game.floor_color = map_data.colors.floor;
	game.ceiling_color = map_data.colors.ceiling;
	game.map_width = map_data.map.width;
	game.map_height = map_data.map.width;

	if (!init_mlx(&game))
	{
		log_msg(ERROR, __FILE__, __LINE__, "MLX initialization failed");
		return (1);
	}
	setup_hooks(&game);
	mlx_loop(game.mlx.mlx);

	return (main_cleanup(&map_data), 0);
}
