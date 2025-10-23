/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:32:38 by hasaliho          #+#    #+#             */
/*   Updated: 2025/10/23 08:11:26 by hasaliho         ###   ########.fr       */
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
        if (game->map[ray->map.y][ray->map.x] == '1')
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
    if (ray->side == 0)
        color = 0xFF0000;
    else
        color = 0x800000;
    y = draw_start;
    while (y <= draw_end)
    {
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

void new_pos(t_game *game, double delta_time)
{
    double speed;
    double rot_speed;
    double angle;
    t_vector tmp_vec;
    
    rot_speed = 3.0 * delta_time;
    speed = 5.0 * delta_time; //? make maybe a define for 5.0
	if(game->keys.move_forward)
    {
        game->player.pos.x = game->player.pos.x + game->player.look_dir.x * speed;
        game->player.pos.y = game->player.pos.y + game->player.look_dir.y * speed;
    }
	if(game->keys.move_back)
    {
        game->player.pos.x = game->player.pos.x - game->player.look_dir.x * speed;
        game->player.pos.y = game->player.pos.y - game->player.look_dir.y * speed;
    }
	if(game->keys.strafe_right)
    {
        game->player.pos.x = game->player.pos.x + game->player.plane.x * speed;
        game->player.pos.y = game->player.pos.y + game->player.plane.y * speed;
    }
	if(game->keys.strafe_left)
    {
        game->player.pos.x = game->player.pos.x - game->player.plane.x * speed;
        game->player.pos.y = game->player.pos.y - game->player.plane.y * speed;
    }
	if(game->keys.rotate_left)
    {
        tmp_vec.x = game->player.look_dir.x;
        angle = -rot_speed;
        game->player.look_dir.x = tmp_vec.x * cos(angle) - game->player.look_dir.y * sin(angle);
        game->player.look_dir.y = tmp_vec.x * sin(angle) + game->player.look_dir.y * cos(angle);

        tmp_vec.x = game->player.plane.x;
        game->player.plane.x = tmp_vec.x * cos(angle) - game->player.plane.y * sin(angle);
        game->player.plane.y = tmp_vec.x * sin(angle) + game->player.plane.y * cos(angle);
    }
	if(game->keys.rotate_right)
    {
        tmp_vec.x = game->player.look_dir.x;
        angle = rot_speed;
        game->player.look_dir.x = tmp_vec.x * cos(angle) - game->player.look_dir.y * sin(angle);
        game->player.look_dir.y = tmp_vec.x * sin(angle) + game->player.look_dir.y * cos(angle);

        tmp_vec.x = game->player.plane.x;
        game->player.plane.x = tmp_vec.x * cos(angle) - game->player.plane.y * sin(angle);
        game->player.plane.y = tmp_vec.x * sin(angle) + game->player.plane.y * cos(angle);
    }
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
    double delta_time;

    current_time = get_time();
    delta_time = current_time - last_time;
    last_time = current_time;
    
    clear_image(&game->mlx, 0x000000, 0x000000);
    new_pos(game, delta_time);
    render(game);
    mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->mlx.img, 0, 0);
    return (0);
}

