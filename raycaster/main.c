/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 09:32:42 by hasaliho          #+#    #+#             */
/*   Updated: 2025/10/22 06:27:53 by hasaliho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/render.h"
#include "include/test_map.h"

int	main(void)
{
	t_game	game;

	init_player(&game.player, 4, 3, 'N');
	game.map = test_map;
	if (!init_mlx(&game))
	{
		printf("Error\nMLX initialization failed\n");
		return (1);
	}
	setup_hooks(&game);
	mlx_loop(game.mlx.mlx);
	return (0);
}
