/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_dda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 09:27:24 by hasaliho          #+#    #+#             */
/*   Updated: 2025/11/27 18:35:06 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/render.h"

static void	calculate_perp_dist(t_ray *ray, t_game *game)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map.x - game->player.pos.x + (1
					- ray->step.x) / 2.0) / ray->dir.x;
	else
		ray->perp_wall_dist = (ray->map.y - game->player.pos.y + (1
					- ray->step.y) / 2.0) / ray->dir.y;
}

static void	step_ray(t_ray *ray)
{
	if (ray->side_dist.x < ray->side_dist.y)
	{
		ray->side_dist.x += ray->delta_dist.x;
		ray->map.x += ray->step.x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist.y += ray->delta_dist.y;
		ray->map.y += ray->step.y;
		ray->side = 1;
	}
}

void	perform_dda(t_ray *ray, t_game *game)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		step_ray(ray);
		if (ray->map.y < 0 || ray->map.x < 0 || ray->map.y >= game->map_height
			|| ray->map.x >= game->map_width)
		{
			hit = 1;
			ray->perp_wall_dist = 1e30;
		}
		else if (game->map[ray->map.y][ray->map.x] == '1')
			hit = 1;
	}
	if (ray->perp_wall_dist != 1e30)
		calculate_perp_dist(ray, game);
}
