/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:57:00 by hasaliho          #+#    #+#             */
/*   Updated: 2025/10/17 09:01:14 by hasaliho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "test_map.h"
#include <mlx.h>

void	init_game(t_game *g)
{
	g->map.width = MAP_WIDTH;
	g->map.height = MAP_HEIGHT;
	g->map.grid = g_test_map;
	g->player.pos_x = 2.5;
	g->player.pos_y = 2.5;
	g->player.dir_x = 1.0;
	g->player.dir_y = 0.0;
	g->player.plane_x = 0.0;
	g->player.plane_y = 0.66;
	g->mlx.win_w = 1024;
	g->mlx.win_h = 640;
}

int	main(void)
{
	t_game	game;

	init_game(&game);
	game.mlx.mlx = mlx_init();
	if (!game.mlx.mlx)
		return (1);
	game.mlx.win = mlx_new_window(game.mlx.mlx, game.mlx.win_w,
			game.mlx.win_h, "cub3d sandbox");
	game.mlx.img = mlx_new_image(game.mlx.mlx, game.mlx.win_w,
			game.mlx.win_h);
	game.mlx.addr = mlx_get_data_addr(game.mlx.img, &game.mlx.bpp,
			&game.mlx.line_len, &game.mlx.endian);
	draw_gradient(&game);
	//cast_debug_ray(&game, game.mlx.win_w / 2);
	mlx_put_image_to_window(game.mlx.mlx, game.mlx.win, game.mlx.img, 0, 0);
	mlx_loop(game.mlx.mlx);
	return (0);
}
