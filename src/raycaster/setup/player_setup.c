/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 07:20:33 by hasaliho          #+#    #+#             */
/*   Updated: 2025/11/28 18:02:41 by hasaliho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/types.h"

void	set_player(double *p_src, double nbr)
{
	*p_src = nbr;
}

void	player_zeroed(t_ray_player *player, int grid_x, int grid_y)
{
	player->pos.x = grid_x + 0.5;
	player->pos.y = grid_y + 0.5;
	player->look_dir.x = 0.0;
	player->look_dir.y = 0.0;
	player->plane.x = 0.0;
	player->plane.y = 0.0;
}

void	init_player(t_ray_player *player, int grid_x, int grid_y,
		char orientation)
{
	double	fov;

	fov = 0.66;
	player_zeroed(player, grid_x, grid_y);
	if (orientation == 'N')
	{
		set_player(&player->look_dir.y, -1.0);
		set_player(&player->plane.x, fov);
	}
	else if (orientation == 'S')
	{
		set_player(&player->look_dir.y, 1.0);
		set_player(&player->plane.x, -fov);
	}
	else if (orientation == 'E')
	{
		set_player(&player->look_dir.x, 1.0);
		set_player(&player->plane.y, fov);
	}
	else if (orientation == 'W')
	{
		set_player(&player->look_dir.x, -1.0);
		set_player(&player->plane.y, -fov);
	}
}
