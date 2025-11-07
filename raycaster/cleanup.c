/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 13:09:50 by hasaliho          #+#    #+#             */
/*   Updated: 2025/11/07 10:31:46 by hasaliho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/render.h"

void	texture_img_destroyer(t_game *g, t_texture *tex)
{
	while (tex)
	{
		if (tex->is_img_created)
		{
			mlx_destroy_image(g->mlx.mlx, tex->img);
			tex->is_img_created = false;
		}
		tex = tex->next;
	}
}

void	cleanup_game(t_game *game)
{
	texture_img_destroyer(game, &game->north_texture);
	if (game->mlx.img)
		mlx_destroy_image(game->mlx.mlx, game->mlx.img);
	if (game->mlx.win)
		mlx_destroy_window(game->mlx.mlx, game->mlx.win);
	if (game->mlx.mlx)
		mlx_destroy_display(game->mlx.mlx);
	if (game->mlx.mlx)
		free(game->mlx.mlx);
	/* 	i = 0;
		if (game->map)
		{
			while (game->map[i])
				free(game->map[i++]);
			free(game->map);
		} */
}
