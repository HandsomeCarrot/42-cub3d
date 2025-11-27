/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:32:38 by hasaliho          #+#    #+#             */
/*   Updated: 2025/11/19 15:17:35 by hasaliho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/render.h"

static void	calculate_ray_steps(t_ray *ray, t_game *game)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (game->player.pos.x - ray->map.x)
			* ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map.x + 1.0 - game->player.pos.x)
			* ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (game->player.pos.y - ray->map.y)
			* ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map.y + 1.0 - game->player.pos.y)
			* ray->delta_dist.y;
	}
}

void	init_ray(t_ray *ray, t_game *game, int x)
{
	double	camera_x;

	camera_x = 2.0 * x / (double)game->mlx.width - 1.0;
	ray->dir.x = game->player.look_dir.x + camera_x * game->player.plane.x;
	ray->dir.y = game->player.look_dir.y + camera_x * game->player.plane.y;
	ray->map.x = (int)game->player.pos.x;
	ray->map.y = (int)game->player.pos.y;
	if (ray->dir.x == 0)
		ray->delta_dist.x = 1e30;
	else
		ray->delta_dist.x = fabs(1.0 / ray->dir.x);
	if (ray->dir.y == 0)
		ray->delta_dist.y = 1e30;
	else
		ray->delta_dist.y = fabs(1.0 / ray->dir.y);
	calculate_ray_steps(ray, game);
}

void	perform_dda(t_ray *ray, t_game *game)
{
	int	hit;

	hit = 0;
	while (!hit)
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
	{
		if (ray->side == 0)
			ray->perp_wall_dist = (ray->map.x - game->player.pos.x + (1
						- ray->step.x) / 2.0) / ray->dir.x;
		else
			ray->perp_wall_dist = (ray->map.y - game->player.pos.y + (1
						- ray->step.y) / 2.0) / ray->dir.y;
	}
}

t_texture	*get_texture(t_game *game, t_ray *ray)
{
	t_texture	*tex;

	if (ray->side == 0)
	{
		if (ray->dir.x > 0)
			tex = &game->west_texture;
		else
			tex = &game->east_texture;
	}
	else
	{
		if (ray->dir.y > 0)
			tex = &game->north_texture;
		else
			tex = &game->south_texture;
	}
	return (tex);
}

void	draw_column(t_ray *ray, t_game *game, int x)
{
	int			line_height;
	int			original_draw_start;
	int			draw_start;
	int			draw_end;
	int			y;
	double		wallX;
	int			texX;
	int			texY;
	t_texture	*tex;
	double		step;
	double		tex_pos;

	line_height = (int)(game->mlx.height / ray->perp_wall_dist);
	original_draw_start = -line_height / 2 + game->mlx.height / 2;
	draw_start = original_draw_start;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + game->mlx.height / 2;
	if (draw_end >= game->mlx.height)
		draw_end = game->mlx.height - 1;
	y = 0;
	while (y < draw_start)
	{
		put_pixel(&game->mlx, x, y, game->ceiling_color);
		y++;
	}
	if (ray->side == 0)
		wallX = game->player.pos.y + ray->perp_wall_dist * ray->dir.y;
	else
		wallX = game->player.pos.x + ray->perp_wall_dist * ray->dir.x;
	wallX = wallX - (int)wallX;
	tex = get_texture(game, ray);
	texX = (int)(wallX * (tex->width));
	step = (double)tex->height / line_height;
	tex_pos = (draw_start - original_draw_start) * step;
	y = draw_start;
	while (y <= draw_end)
	{
		texY = (int)tex_pos;
		if (texY < 0)
			texY = 0;
		if (texY >= tex->height)
			texY = tex->height - 1;
		put_pixel(&game->mlx, x, y, get_pixel_color(tex, texX, texY));
		tex_pos += step;
		y++;
	}
	y = draw_end + 1;
	while (y < game->mlx.height)
	{
		put_pixel(&game->mlx, x, y, game->floor_color);
		y++;
	}
}

int	render(t_game *game)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < game->mlx.width)
	{
		init_ray(&ray, game, x);
		perform_dda(&ray, game);
		draw_column(&ray, game, x);
		x++;
	}
	return (1);
}

int	render_loop(t_game *game)
{
	static double	last_time = 0;
	double			current_time;
	double			tile_size;

	current_time = get_time();
	tile_size = get_tile_size(game);
	game->player.delta_time = current_time - last_time;
	last_time = current_time;
	new_pos(game);
	render(game);
	draw_minimap(game);
	draw_minimap_rays(game, tile_size);
	draw_player_triangle(game, tile_size);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->mlx.img, 0, 0);
#ifdef __APPLE__
	mlx_do_sync(game->mlx.mlx);
#endif
	return (0);
}
