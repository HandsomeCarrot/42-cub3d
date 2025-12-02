/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:26:09 by vpoka             #+#    #+#             */
/*   Updated: 2025/12/02 14:22:36 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	move_info(t_game *game, t_map_data *config)
{
	if (!game || !config)
	{
		log_msg(WARNING, __FILE__, __LINE__, LOG_INVALID_PARAM);
		return (1);
	}
	init_player(&game->player, config->player.pos_x, config->player.pos_y,
		config->player.orientation);
	game->map = config->map.layout;
	game->floor_color = config->colors.floor;
	game->ceiling_color = config->colors.ceiling;
	game->map_width = config->map.width;
	game->map_height = config->map.width;
	return (0);
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
	ft_bzero(&map_data, sizeof(t_map_data));
	if (parse(argc, argv, &map_data))
	{
		main_cleanup(&map_data);
		return (1);
	}
	ft_bzero(&game, sizeof(t_game));
	if (move_info(&game, &map_data) || !init_mlx(&game, &map_data))
	{
		log_msg(ERROR, __FILE__, __LINE__, "MLX initialization failed");
		main_cleanup(&map_data);
		return (1);
	}
	setup_hooks(&game);
	mlx_loop(game.mlx.mlx);
	return (main_cleanup(&map_data), 0);
}
