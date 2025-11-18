/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:06:00 by hasaliho          #+#    #+#             */
/*   Updated: 2025/11/18 17:26:58 by hasaliho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/render.h"

int	color_picker(t_game *game, int map_y, int map_x)
{
	char	c;

	c = game->map[map_y][map_x];
	if (c == '1')
		return (COLOR_GRAY);
	else
		return (COLOR_WHITE);
}

void	get_map_dimensions(t_game *game, int *width, int *height)
{
	int	w;
	int	h;
	int	current_row_len;

	w = 0;
	h = 0;
	while (game->map[h])
	{
		current_row_len = 0;
		while (game->map[h][current_row_len])
		{
			current_row_len++;
		}
		if (current_row_len > w)
			w = current_row_len;
		h++;
	}
	*width = w;
	*height = h;
}

double	get_tile_size(t_game *game)
{
	t_point	map_grid;
	t_point	ratio;
	t_point	minimap_max;
	double	tile_size;

	get_map_dimensions(game, &map_grid.x, &map_grid.y);
	minimap_max.x = game->mlx.width / 4;
	minimap_max.y = game->mlx.height / 4;
	ratio.x = (double)minimap_max.x / (double)map_grid.x;
	ratio.y = (double)minimap_max.y / (double)map_grid.y;
	tile_size = fmin(ratio.x, ratio.y);
	return (tile_size);
}

static void	fill_tile(t_game *game, int map_x, int map_y, double tile_size)
{
	int		pixel_x;
	int		pixel_y;
	int		screen_x;
	int		screen_y;
	int		color;

	color = color_picker(game, map_y, map_x);
	pixel_y = 0;
	while (pixel_y < (int)tile_size)
	{
		pixel_x = 0;
		screen_y = map_y * tile_size + pixel_y;
		while (pixel_x < (int)tile_size)
		{
			screen_x = map_x * tile_size + pixel_x;
			put_pixel(&game->mlx, screen_x, screen_y, color);
			pixel_x++;
		}
		pixel_y++;
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
	double	delta_x;
	double	delta_y;
	int		steps;
	double	x;
	double	y;
	double	x_inc;
	double	y_inc;

	delta_x = p2.x - p1.x;
	delta_y = p2.y - p1.y;
	if (fabs(delta_x) > fabs(delta_y))
		steps = fabs(delta_x);
	else
		steps = fabs(delta_y);
	x_inc = delta_x / (double)steps;
	y_inc = delta_y / (double)steps;
	x = p1.x;
	y = p1.y;
	while (steps >= 0)
	{
		put_pixel(mlx, (int)x, (int)y, color);
		x += x_inc;
		y += y_inc;
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
	t_ray	ray;
	t_point	player_pos;
	t_point	hit_pos;
	int		x;
	double	hit_world_x;
	double	hit_world_y;

	player_pos.x = (int)(game->player.pos.x * tile_size);
	player_pos.y = (int)(game->player.pos.y * tile_size);
	x = 0;
	while (x < game->mlx.width)
	{
		init_ray(&ray, game, x);
		perform_dda(&ray, game);
		hit_world_x = game->player.pos.x + ray.perp_wall_dist * ray.dir.x;
		hit_world_y = game->player.pos.y + ray.perp_wall_dist * ray.dir.y;
		hit_pos.x = (int)(hit_world_x * tile_size);
		hit_pos.y = (int)(hit_world_y * tile_size);
		draw_line(&game->mlx, player_pos, hit_pos, COLOR_YELLOW);
		x += 10;
	}
}
