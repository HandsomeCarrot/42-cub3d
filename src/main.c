/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:26:09 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/28 18:04:23 by hasaliho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include "./raycaster/include/render.h"
#include "./raycaster/include/types.h"

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
	t_game		game;
	t_map_data	map_data;

	game = (t_game){0};
	log_msg(DEBUG, __FILE__, __LINE__, "executing cub3d");
	ft_bzero(&map_data, sizeof(t_map_data));
	if (parse(argc, argv, &map_data))
		return (main_cleanup(&map_data), 1);
	init_player(&game.player, map_data.player.pos_x, map_data.player.pos_y,
		map_data.player.orientation);
	game.map = map_data.map.layout;
	game.floor_color = COLOR_GRAY;
	game.ceiling_color = COLOR_BLACK;
	get_map_dimensions(&game, &game.map_width, &game.map_height);
	if (!init_mlx(&game, &map_data))
	{
		printf("Error\nMLX initialization failed\n");
		return (1);
	}
	setup_hooks(&game);
	mlx_loop(game.mlx.mlx);
	return (main_cleanup(&map_data), 0);
}
