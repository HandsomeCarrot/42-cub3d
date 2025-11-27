/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:06:00 by hasaliho          #+#    #+#             */
/*   Updated: 2025/11/21 17:32:30 by hasaliho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/render.h"

static void	fill_tile(t_game *game, int map_x, int map_y, double tile_size)
{
	t_point	pixel;
	int		screen_x;
	int		screen_y;
	int		color;

	color = color_picker(game, map_y, map_x);
	pixel.y = 0;
	while (pixel.y < (int)tile_size)
	{
		pixel.x = 0;
		screen_y = map_y * tile_size + pixel.y;
		while (pixel.x < (int)tile_size)
		{
			screen_x = map_x * tile_size + pixel.x;
			put_pixel(&game->mlx, screen_x, screen_y, color);
			pixel.x++;
		}
		pixel.y++;
	}
}

void	draw_minimap(t_game *game)
{
	int		map_x;
	int		map_y;
	double	tile_size;

	tile_size = get_tile_size(game);
	map_y = 0;
	while (game->map[map_y])
	{
		map_x = 0;
		while (game->map[map_y][map_x])
		{
			fill_tile(game, map_x, map_y, tile_size);
			map_x++;
		}
		map_y++;
	}
}

void	draw_line(t_mlx *mlx, t_point p1, t_point p2, int color)
{
	t_vector	delta;
	int			steps;
	double		x;
	double		y;
	t_vector	inc;

	delta.x = p2.x - p1.x;
	delta.y = p2.y - p1.y;
	if (fabs(delta.x) > fabs(delta.y))
		steps = fabs(delta.x);
	else
		steps = fabs(delta.y);
	inc.x = delta.x / (double)steps;
	inc.y = delta.y / (double)steps;
	x = p1.x;
	y = p1.y;
	while (steps >= 0)
	{
		put_pixel(mlx, (int)x, (int)y, color);
		x += inc.x;
		y += inc.y;
		steps--;
	}
}

void	draw_player_triangle(t_game *game, double tile_size)
{
	double	fwd_x;
	double	fwd_y;
	t_point	p1;
	t_point	p2;
	t_point	p3;

	fwd_x = game->player.look_dir.x;
	fwd_y = game->player.look_dir.y;
	game->player.plane.x = game->player.plane.x;
	game->player.plane.y = game->player.plane.y;
	p1.x = (int)((game->player.pos.x + (P1_LOCAL_X * game->player.plane.x
					+ P1_LOCAL_Y * fwd_x)) * tile_size);
	p1.y = (int)((game->player.pos.y + (P1_LOCAL_X * game->player.plane.y
					+ P1_LOCAL_Y * fwd_y)) * tile_size);
	p2.x = (int)((game->player.pos.x + (P2_LOCAL_X * game->player.plane.x
					+ P2_LOCAL_Y * fwd_x)) * tile_size);
	p2.y = (int)((game->player.pos.y + (P2_LOCAL_X * game->player.plane.y
					+ P2_LOCAL_Y * fwd_y)) * tile_size);
	p3.x = (int)((game->player.pos.x + (P3_LOCAL_X * game->player.plane.x
					+ P3_LOCAL_Y * fwd_x)) * tile_size);
	p3.y = (int)((game->player.pos.y + (P3_LOCAL_X * game->player.plane.y
					+ P3_LOCAL_Y * fwd_y)) * tile_size);
	draw_line(&game->mlx, p1, p2, COLOR_RED);
	draw_line(&game->mlx, p2, p3, COLOR_RED);
	draw_line(&game->mlx, p3, p1, COLOR_RED);
}

void	draw_minimap_rays(t_game *game, double tile_size)
{
	t_ray		ray;
	t_point		player_pos;
	t_point		hit_pos;
	int			x;
	t_vector	hit_world;

	player_pos.x = (int)(game->player.pos.x * tile_size);
	player_pos.y = (int)(game->player.pos.y * tile_size);
	x = 0;
	while (x < game->mlx.width)
	{
		init_ray(&ray, game, x);
		perform_dda(&ray, game);
		hit_world.x = game->player.pos.x + ray.perp_wall_dist * ray.dir.x;
		hit_world.y = game->player.pos.y + ray.perp_wall_dist * ray.dir.y;
		hit_pos.x = (int)(hit_world.x * tile_size);
		hit_pos.y = (int)(hit_world.y * tile_size);
		draw_line(&game->mlx, player_pos, hit_pos, COLOR_YELLOW);
		x += 10;
	}
}
