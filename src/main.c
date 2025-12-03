/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:26:09 by vpoka             #+#    #+#             */
/*   Updated: 2025/12/03 16:39:42 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	move_info(t_game *game, t_map_data *config)
{
	init_player(&game->player, config->player.pos_x, config->player.pos_y,
		config->player.orientation);
	game->map = config->map.layout;
	game->floor_color = config->colors.floor;
	game->ceiling_color = config->colors.ceiling;
	game->map_width = config->map.width;
	game->map_height = config->map.width;
}

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
	t_game		game;

	log_msg(DEBUG, __FILE__, __LINE__, "executing cub3d");
	map_data = (t_map_data){0};
	if (parse(argc, argv, &map_data))
	{
		main_cleanup(&map_data);
		return (1);
	}
	game = (t_game){0};
	move_info(&game, &map_data);
	if (!init_mlx(&game, &map_data))
	{
		log_msg(ERROR, __FILE__, __LINE__, "MLX initialization failed");
		free_image_paths(&map_data);
		return (1);
	}
	free_image_paths(&map_data);
	setup_hooks(&game);
	mlx_loop(game.mlx.mlx);
	return (main_cleanup(&map_data), 0);
}
