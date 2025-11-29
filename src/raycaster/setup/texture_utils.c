/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:42:32 by hasaliho          #+#    #+#             */
/*   Updated: 2025/11/29 00:54:38 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/raycaster/render.h"

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

int	load_all_textures(t_game *game, t_map_data *config)
{
	init_texture_list(game);
	if (!load_texture(game, &game->north_texture, config->images.north_wall)
		|| !load_texture(game, &game->south_texture, config->images.south_wall)
		|| !load_texture(game, &game->east_texture, config->images.east_wall)
		|| !load_texture(game, &game->west_texture, config->images.west_wall))
		return (0);
	return (1);
}
