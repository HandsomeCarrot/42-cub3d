/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 07:31:49 by hasaliho          #+#    #+#             */
/*   Updated: 2025/10/29 08:28:51 by hasaliho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "cub3d.h"
#include "./include/render.h"
#include "./include/types.h"

void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	int	offset;

	if (x < 0 || x >= mlx->width || y < 0 || y >= mlx->height)
		return ;
	offset = (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int *)(mlx->img_data + offset) = color;
}

static void	cleanup_mlx(t_game *game)
{
	if (game->mlx.img)
		mlx_destroy_image(game->mlx.mlx, game->mlx.img);
	if (game->mlx.win)
		mlx_destroy_window(game->mlx.mlx, game->mlx.win);
}

int	init_mlx(t_game *game)
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
	game->mlx.img = mlx_new_image(game->mlx.mlx, game->mlx.width,
			game->mlx.height);
	if (!game->mlx.img)
	{
		cleanup_mlx(game);
		return (0);
	}
	game->mlx.img_data = mlx_get_data_addr(game->mlx.img,
			&game->mlx.bits_per_pixel, &game->mlx.line_length,
			&game->mlx.endian);

	char *north_path = "./textures/north.xpm"; // Placeholder
	char *south_path = "./textures/south.xpm"; // Placeholder
	char *east_path = "./textures/east.xpm";   // Placeholder
	char *west_path = "./textures/west.xpm";   // Placeholder
	return (1);
}

