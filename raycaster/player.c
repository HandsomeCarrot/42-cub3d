/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 07:20:33 by hasaliho          #+#    #+#             */
/*   Updated: 2025/10/22 11:00:17 by hasaliho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/types.h"

void	init_player(t_player *player, int grid_x, int grid_y, char orientation)
{
	double	fov;

	fov = 0.66;
	player->pos.x = grid_x + 0.5;
	player->pos.y = grid_y + 0.5;
	if (orientation == 'N')
	{
		player->look_dir.x = 0.0;
		player->look_dir.y = -1.0;
		player->plane.x = fov;
		player->plane.y = 0.0;
	}
	else if (orientation == 'S')
	{
		player->look_dir.x = 0.0;
		player->look_dir.y = 1.0;
		player->plane.x = -fov;
		player->plane.y = 0.0;
	}
	else if (orientation == 'E')
	{
		player->look_dir.x = 1.0;
		player->look_dir.y = 0.0;
		player->plane.x = 0.0;
		player->plane.y = fov;
	}
	else if (orientation == 'W')
	{
		player->look_dir.x = -1.0;
		player->look_dir.y = 0.0;
		player->plane.x = 0.0;
		player->plane.y = -fov;
	}
}
