/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 07:31:49 by hasaliho          #+#    #+#             */
/*   Updated: 2025/11/27 18:35:06 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/render.h"

static int	init_mlx_window(t_game *game)
{
	game->mlx.mlx = mlx_init();
	if (!game->mlx.mlx)
		return (0);
	mlx_get_screen_size(game->mlx.mlx, &game->mlx.width, &game->mlx.height);
	if (game->mlx.width <= 0 || game->mlx.height <= 0)
	{
		game->mlx.width = 800;
		game->mlx.height = 600;
	}
	game->mlx.win = mlx_new_window(game->mlx.mlx, game->mlx.width,
			game->mlx.height, "cub3D");
	if (!game->mlx.win)
		return (0);
	return (1);
}

static int	init_mlx_image(t_game *game)
{
	game->mlx.img = mlx_new_image(game->mlx.mlx, game->mlx.width,
			game->mlx.height);
	if (!game->mlx.img)
		return (0);
	game->mlx.img_data = mlx_get_data_addr(game->mlx.img,
			&game->mlx.bits_per_pixel, &game->mlx.line_length,
			&game->mlx.endian);
	if (!game->mlx.img_data)
		return (0);
	game->mlx.bytes_per_pixel = game->mlx.bits_per_pixel >> 3;
	return (1);
}

int	init_mlx(t_game *game)
{
	if (!init_mlx_window(game))
	{
		cleanup_game(game);
		return (0);
	}
	if (!init_mlx_image(game))
	{
		cleanup_game(game);
		return (0);
	}
	if (!load_all_textures(game))
	{
		cleanup_game(game);
		return (0);
	}
	return (1);
}
