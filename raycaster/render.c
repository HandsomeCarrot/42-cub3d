/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:32:38 by hasaliho          #+#    #+#             */
/*   Updated: 2025/10/29 19:45:13 by hasaliho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/render.h"

void init_ray(t_ray *ray, t_game *game, int x)
{
	double camera_x;

	camera_x = 2.0 * x / (double)game->mlx.width - 1.0;
	ray->dir.x = game->player.look_dir.x + camera_x * game->player.plane.x;
	ray->dir.y = game->player.look_dir.y + camera_x * game->player.plane.y;
	ray->map.x = (int)game->player.pos.x;
	ray->map.y = (int)game->player.pos.y;
	ray->delta_dist.x = fabs(1.0 / ray->dir.x); //!: was wenn x = 0
	ray->delta_dist.y = fabs(1.0 / ray->dir.y); //!: was wenn y = 0
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (game->player.pos.x - ray->map.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map.x + 1.0 - game->player.pos.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (game->player.pos.y - ray->map.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map.y + 1.0 - game->player.pos.y) * ray->delta_dist.y;
	}
}

void perform_dda(t_ray *ray, t_game *game)
{
    int hit;

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
        if (game->map[ray->map.y][ray->map.x] == '1') //!without collision this line creates a segfault when out of bounds easy fix
            hit = 1;
    }

    if (ray->side == 0)
        ray->perp_wall_dist = (ray->map.x - game->player.pos.x + (1 - ray->step.x) / 2.0) / ray->dir.x;
    else
        ray->perp_wall_dist = (ray->map.y - game->player.pos.y + (1 - ray->step.y) / 2.0) / ray->dir.y;
}

void draw_column(t_ray *ray, t_game *game, int x)
{
    int line_height;
    int draw_start;
    int draw_end;
    int y;
    int color;

    line_height = (game->mlx.height / ray->perp_wall_dist);
    draw_start = -line_height / 2 + game->mlx.height / 2;
    if (draw_start < 0)
        draw_start = 0;
    draw_end = line_height / 2 + game->mlx.height / 2;
    if (draw_end >= game->mlx.height)
        draw_end = game->mlx.height - 1;
    y = draw_start;
    while (y <= draw_end)
    {
        if (ray->side == 0)
            color = get_pixel_color(&game->north_texture, x, y);
        else
            color = get_pixel_color(&game->south_texture, x, y);
        put_pixel(&game->mlx, x, y, color);
        y++;
    }
}

int render(t_game *game)
{
    int     x;
    t_ray   ray;
    
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

bool	check_wall(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_x < 0)
		return (true);
	if (game->map[map_y] == NULL)
		return (true);
	if (game->map[map_y][map_x] == '\0')
		return (true);
	if (game->map[map_y][map_x] == '1')
		return (true);
	return (false);
}

void    perform_rot(t_game *game, double angle)
{
    double tmp_vec;

    tmp_vec = game->player.look_dir.x;
    game->player.look_dir.x = tmp_vec * cos(angle) - game->player.look_dir.y * sin(angle);
    game->player.look_dir.y = tmp_vec * sin(angle) + game->player.look_dir.y * cos(angle);

    tmp_vec = game->player.plane.x;
    game->player.plane.x = tmp_vec * cos(angle) - game->player.plane.y * sin(angle);
    game->player.plane.y = tmp_vec * sin(angle) + game->player.plane.y * cos(angle);
}

void    perform_move(t_game *game, char op, t_vector v2)
{
    t_vector tmp;
    double move_speed = game->player.speed;
    move_speed = move_speed * game->player.delta_time; //? make maybe a define for 5.0
    if(op == '+')
    {
        tmp.x = game->player.pos.x + v2.x * move_speed;
        tmp.y = game->player.pos.y + v2.y * move_speed;
         if(!check_wall(game, tmp.x, tmp.y))
         {
             game->player.pos.x = tmp.x;
             game->player.pos.y = tmp.y;
         }
    }
    else
    {
        tmp.x = game->player.pos.x - v2.x * move_speed;
        tmp.y = game->player.pos.y - v2.y * move_speed;
        if(!check_wall(game, tmp.x, tmp.y))
         {
             game->player.pos.x = tmp.x;
             game->player.pos.y = tmp.y;
         }
    }
}

void new_pos(t_game *game)
{
    double rot_speed;
    
    if(game->keys.shift)
        game->player.speed = 12.0;
    else
        game->player.speed = 5.0;
    rot_speed = 3.0 * game->player.delta_time;
	if(game->keys.move_forward)
        perform_move(game, '+', game->player.look_dir);
	if(game->keys.move_back)
        perform_move(game, '-', game->player.look_dir);
	if(game->keys.strafe_right)
        perform_move(game, '+', game->player.plane);
	if(game->keys.strafe_left)
        perform_move(game, '-', game->player.plane);
	if(game->keys.rotate_left)
        perform_rot(game, -rot_speed);
	if(game->keys.rotate_right)
        perform_rot(game, rot_speed);
}

void clear_image(t_mlx *mlx, int floor_color, int ceiling_color)
{
    int x;
    int y;
    int half_height;

    half_height = mlx->height / 2;
    y = 0;
    while (y < mlx->height)
    {
        x = 0;
        while (x < mlx->width)
        {
            if (y < half_height)
                put_pixel(mlx, x, y, ceiling_color);
            else
                put_pixel(mlx, x, y, floor_color);
            x++;
        }
        y++;
    }
}

int render_loop(t_game *game)
{
    static double last_time = 0;
    double current_time;

    current_time = get_time();
    double tile_size = get_tile_size(game);
    game->player.delta_time = current_time - last_time;
    last_time = current_time;
    
    clear_image(&game->mlx, COLOR_BLACK, COLOR_BLACK);
    new_pos(game);
    render(game);
    draw_minimap(game);
    draw_minimap_rays(game, tile_size);
    draw_player_triangle(game, tile_size);
    mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->mlx.img, 0, 0);
    return (0);
}

