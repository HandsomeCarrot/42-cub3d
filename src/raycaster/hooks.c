/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 11:07:26 by hasaliho          #+#    #+#             */
/*   Updated: 2025/11/27 18:38:45 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/render.h"

int	close_handler(void *param)
{
	cleanup_game((t_game *)param);
	exit(0);
	return (0);
}

int	key_release_handler(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == XK_W || keycode == XK_w || keycode == XK_Up)
		game->keys.move_forward = false;
	else if (keycode == XK_S || keycode == XK_s || keycode == XK_Down)
		game->keys.move_back = false;
	else if (keycode == XK_D || keycode == XK_d)
		game->keys.strafe_right = false;
	else if (keycode == XK_A || keycode == XK_a)
		game->keys.strafe_left = false;
	else if (keycode == XK_Left)
		game->keys.rotate_left = false;
	else if (keycode == XK_Right)
		game->keys.rotate_right = false;
	else if (keycode == XK_Shift_L || keycode == XK_Shift_R)
		game->keys.shift = false;
	return (0);
}

int	key_handler(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == XK_Escape)
		close_handler(param);
	else if (keycode == XK_W || keycode == XK_w || keycode == XK_Up)
		game->keys.move_forward = true;
	else if (keycode == XK_S || keycode == XK_s || keycode == XK_Down)
		game->keys.move_back = true;
	else if (keycode == XK_D || keycode == XK_d)
		game->keys.strafe_right = true;
	else if (keycode == XK_A || keycode == XK_a)
		game->keys.strafe_left = true;
	else if (keycode == XK_Left)
		game->keys.rotate_left = true;
	else if (keycode == XK_Right)
		game->keys.rotate_right = true;
	else if (keycode == XK_Shift_L || keycode == XK_Shift_R)
		game->keys.shift = true;
	return (0);
}

void	setup_hooks(t_game *game)
{
	mlx_hook(game->mlx.win, KeyPress, KeyPressMask, key_handler, game);
	mlx_hook(game->mlx.win, KeyRelease, KeyReleaseMask, key_release_handler,
		game);
	mlx_hook(game->mlx.win, DestroyNotify, NoEventMask, close_handler, game);
	mlx_loop_hook(game->mlx.mlx, render_loop, game);
}
