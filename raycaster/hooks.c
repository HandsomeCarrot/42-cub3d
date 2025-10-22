/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:07:26 by hasaliho          #+#    #+#             */
/*   Updated: 2025/10/22 06:05:11 by hasaliho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/render.h"

int close_handler(void *param)
{
	cleanup_game((t_game *)param);
	exit(0);
	return (0);
}

int	key_handler(int keycode, void *param)
{
	if (keycode == 65307)
	{
		close_handler(param);
	}
	return (0);
}

void setup_hooks(t_game *game)
{
	mlx_hook(game->mlx.win, 2, 1L<<0, key_handler, game);
	mlx_hook(game->mlx.win, 17, 0, close_handler, game);
	mlx_loop_hook(game->mlx.mlx, render_loop, game);
}



