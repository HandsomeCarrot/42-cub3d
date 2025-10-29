/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 07:31:49 by hasaliho          #+#    #+#             */
/*   Updated: 2025/10/29 19:19:00 by hasaliho         ###   ########.fr       */
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

static void	init_texture_node(t_texture *texture)
{
	texture->img = NULL;
	texture->img_data = NULL;
	texture->width = 0;
	texture->height = 0;
	texture->bits_per_pixel = 0;
	texture->line_length = 0;
	texture->endian = 0;
	texture->is_img_created = false;
	texture->next = NULL;
}

static void	init_texture_list(t_game *game)
{
	init_texture_node(&game->north_texture);
	init_texture_node(&game->south_texture);
	init_texture_node(&game->east_texture);
	init_texture_node(&game->west_texture);
	game->north_texture.next = &game->south_texture;
	game->south_texture.next = &game->east_texture;
	game->east_texture.next = &game->west_texture;
}

int	get_pixel_color(t_texture *tex, int x, int y)
{
	int offset;
	int color;

	if(x < 0 || y < 0 || x >= tex->width || y >= tex->height)
		return (COLOR_MAGENTA);
	offset = y * tex->line_length + x * (tex->bits_per_pixel / 8);
	color = *(int *)tex->img_data + offset;
	return (color);
}

static int	load_texture(t_game *g, t_texture *dest, const char *path)
{
	printf("loading\n"); //?need to remove
	dest->img = mlx_xpm_file_to_image(g->mlx.mlx, (char *)path,
			&dest->width, &dest->height);
	if (!dest->img)
	{
		cleanup_game(g);
		return (0);
	}
	dest->is_img_created = true;
	printf("img is loaded\n"); //?need to remove
	dest->img_data = mlx_get_data_addr(dest->img, &dest->bits_per_pixel,
			&dest->line_length, &dest->endian);
	if (!dest->img_data)
	{
		cleanup_game(g);
		return (0);
	}
	return (1);
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
		cleanup_game(game);
		return (0);
	}
	game->mlx.img_data = mlx_get_data_addr(game->mlx.img,
			&game->mlx.bits_per_pixel, &game->mlx.line_length,
			&game->mlx.endian);

	init_texture_list(game);

	char *north_path = "./textures/xpm/Brick.xpm"; // Placeholder
	char *south_path = "./textures/xpm/Metal.xpm"; // Placeholder
	char *east_path = "./textures/xpm/Wood.xpm";   // Placeholder
	char *west_path = "./textures/xpm/Stone.xpm";   // Placeholder

	if (!load_texture(game, &game->north_texture, north_path)
		|| !load_texture(game, &game->south_texture, south_path)
		|| !load_texture(game, &game->east_texture, east_path)
		|| !load_texture(game, &game->west_texture, west_path))
		{
			return (0);
		}
	return (1);
}

