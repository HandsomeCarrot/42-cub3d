/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 09:32:42 by hasaliho          #+#    #+#             */
/*   Updated: 2025/10/21 15:11:26 by hasaliho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/render.h"

int	main(void)
{
	t_game	game;
	int		x;
	int		y;

	if (!init_mlx(&game))
	{
		printf("Error\nMLX initialization failed\n");
		return (1);
	}
	y = 0;
	while (y < game.mlx.height)
	{
		x = 0;
		while (x < game.mlx.width)
		{
			put_pixel(&game.mlx, x, y, 0x00FF0000);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game.mlx.mlx, game.mlx.win, game.mlx.img, 0, 0);
	setup_hooks(&game);
	render(&game);
	mlx_loop(game.mlx.mlx);
	return (0);
}
