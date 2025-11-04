/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 09:13:56 by hasaliho          #+#    #+#             */
/*   Updated: 2025/11/04 16:21:32 by hasaliho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/render.h"

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

bool	check_wall_collision(t_game *game, double x, double y)
{
	if(!check_wall(game, x - RADIUS, y - RADIUS) &&
	!check_wall(game, x + RADIUS, y + RADIUS) &&
	!check_wall(game, x + RADIUS, y - RADIUS) &&
	!check_wall(game, x - RADIUS, y + RADIUS))
		return (false);

	return (true);
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
		if(!check_wall_collision(game, tmp.x, game->player.pos.y))
			game->player.pos.x = tmp.x;
		if(!check_wall_collision(game, game->player.pos.x, tmp.y))
			game->player.pos.y = tmp.y;
	}
    else
    {
        tmp.x = game->player.pos.x - v2.x * move_speed;
        tmp.y = game->player.pos.y - v2.y * move_speed;
		if(!check_wall_collision(game, tmp.x, game->player.pos.y))
			game->player.pos.x = tmp.x;
		if(!check_wall_collision(game, game->player.pos.x, tmp.y))
			game->player.pos.y = tmp.y;
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