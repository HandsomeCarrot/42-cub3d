/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:32:38 by hasaliho          #+#    #+#             */
/*   Updated: 2025/10/21 15:17:37 by hasaliho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/render.h"

int render(t_game *game)
{
	int x;
	double camera_x;
	t_vector    ray_dir;

	x = 0;
	while (x < game->mlx.width)
	{
		camera_x = 2.0 * x / (double)game->mlx.width - 1.0;
		ray_dir.x = game->player.look_dir.x + camera_x * game->player.plane.x;
		ray_dir.y = game->player.look_dir.y + camera_x * game->player.plane.y;
		printf("Column: %d, ray_dir: (%f, %f)\n", x, ray_dir.x, ray_dir.y);
		x++;
	}
	return (1);
}
