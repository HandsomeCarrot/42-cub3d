/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:42:32 by hasaliho          #+#    #+#             */
/*   Updated: 2025/11/25 14:47:29 by hasaliho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/render.h"

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

static int	load_texture(t_game *g, t_texture *dest, const char *path)
{
	dest->img = mlx_xpm_file_to_image(g->mlx.mlx, (char *)path, &dest->width,
			&dest->height);
	if (!dest->img)
		return (0);
	dest->is_img_created = true;
	dest->img_data = mlx_get_data_addr(dest->img, &dest->bits_per_pixel,
			&dest->line_length, &dest->endian);
	dest->bytes_per_pixel = dest->bits_per_pixel >> 3;
	if (!dest->img_data)
		return (0);
	return (1);
}

int	load_all_textures(t_game *game)
{
	static char	*north_path = "./textures/xpm/Futuristic_1024.xpm";
	static char	*south_path = "./textures/xpm/Metal_1024.xpm";
	static char	*east_path = "./textures/xpm/Wood_1024.xpm";
	static char	*west_path = "./textures/xpm/Stone_1024.xpm";

	init_texture_list(game);
	if (!load_texture(game, &game->north_texture, north_path)
		|| !load_texture(game, &game->south_texture, south_path)
		|| !load_texture(game, &game->east_texture, east_path)
		|| !load_texture(game, &game->west_texture, west_path))
		return (0);
	return (1);
}
