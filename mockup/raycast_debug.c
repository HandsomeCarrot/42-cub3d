/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_debug.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 07:21:00 by hasaliho          #+#    #+#             */
/*   Updated: 2025/10/17 15:27:40 by hasaliho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include <math.h>
#include <stdio.h>

static void	init_ray(t_player *p, int x, int w, double *ray)
{
	double	camera_x;

	camera_x = 2.0 * x / (double)w - 1.0;
	ray[0] = p->dir_x + p->plane_x * camera_x;
	ray[1] = p->dir_y + p->plane_y * camera_x;
	printf("  cameraX=%.3f  rayDir=(%.3f, %.3f)\n",
		camera_x, ray[0], ray[1]);
}

static void	init_dda(t_player *p, double *ray, int *map, double *side,
	double *delta, int *step)
{
	map[0] = (int)p->pos_x;
	map[1] = (int)p->pos_y;
	delta[0] = fabs(1.0 / ray[0]);
	delta[1] = fabs(1.0 / ray[1]);
	if (ray[0] < 0)
	{
		step[0] = -1;
		side[0] = (p->pos_x - map[0]) * delta[0];
	}
	else
	{
		step[0] = 1;
		side[0] = (map[0] + 1.0 - p->pos_x) * delta[0];
	}
	if (ray[1] < 0)
	{
		step[1] = -1;
		side[1] = (p->pos_y - map[1]) * delta[1];
	}
	else
	{
		step[1] = 1;
		side[1] = (map[1] + 1.0 - p->pos_y) * delta[1];
	}
/* 	printf("  mapXY=(%d,%d) step=(%d,%d) delta=(%.3f,%.3f) side=(%.3f,%.3f)\n",
		map[0], map[1], step[0], step[1], delta[0], delta[1], side[0], side[1]); */
}

static int	run_dda(t_map *m, int *map_xy, double *side,
	double *delta, int *step)
{
	int	hit_side;

	while (1)
	{
		if (side[0] < side[1])
		{
			side[0] += delta[0];
			map_xy[0] += step[0];
			hit_side = 0;
		}
		else
		{
			side[1] += delta[1];
			map_xy[1] += step[1];
			hit_side = 1;
		}
		if (map_xy[0] < 0 || map_xy[0] >= m->width
			|| map_xy[1] < 0 || map_xy[1] >= m->height)
			break ;
		if (m->grid[map_xy[1]][map_xy[0]] == '1')
		{
			//printf("  HIT at (%d,%d) side=%d\n", map_xy[0], map_xy[1], hit_side);
			return (hit_side);
		}
	}
	//printf("  OUT OF BOUNDS\n");
	return (-1);
}

static void	draw_column(t_mlx *mlx, int x, double perp_dist, int side)
{
	int	line_h;
	int	draw_start;
	int	draw_end;
	int	y;
	int	color;
	
	line_h = (int)(mlx->win_h / perp_dist);
	draw_start = -line_h / 2 + mlx->win_h / 2;
	if (draw_start < 0)
	draw_start = 0;
draw_end = line_h / 2 + mlx->win_h / 2;
if (draw_end >= mlx->win_h)
draw_end = mlx->win_h - 1;
color = 0xFFFFFF;
if (side == 1)
color = 0x808080;
y = draw_start;
while (y < draw_end)
{
	put_pixel(mlx, x, y, color);
	y++;
}
}

void	cast_debug_ray(t_game *g, int x)
{
	double	ray[2];
	int		map_xy[2];
	double	side[2];
	double	delta[2];
	int		step[2];
	int		hit_side;
	double	perp_dist;

	printf("Column %d:\n", x);
	init_ray(&g->player, x, g->mlx.win_w, ray);
	init_dda(&g->player, ray, map_xy, side, delta, step);
	hit_side = run_dda(&g->map, map_xy, side, delta, step);
	if (hit_side == 0)
		perp_dist = (map_xy[0] - g->player.pos_x
				+ (1 - step[0]) / 2.0) / ray[0];
	else if (hit_side == 1)
		perp_dist = (map_xy[1] - g->player.pos_y
				+ (1 - step[1]) / 2.0) / ray[1];
	else
		perp_dist = 999.0;
	if (hit_side >= 0)
		draw_column(&g->mlx, x, perp_dist, hit_side);

}
