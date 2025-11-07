/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 09:13:56 by hasaliho          #+#    #+#             */
/*   Updated: 2025/11/07 10:09:30 by hasaliho         ###   ########.fr       */
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
	if (check_wall(game, x - RADIUS, y - RADIUS))
		return (true);
	if (check_wall(game, x + RADIUS, y + RADIUS))
		return (true);
	if (check_wall(game, x + RADIUS, y - RADIUS))
		return (true);
	if (check_wall(game, x - RADIUS, y + RADIUS))
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

void precise_wall_check(t_game *game, double *p_axis1, double target_axis1, double axis2_fixed, bool is_x)
{
	double curr_pos = *p_axis1;
		double dist = fabs(target_axis1 - curr_pos);
		if (dist < 0.0001)  // zero
			return;
		int num_steps = (int)ceil(dist / SAFE_STEP);
		double step_size = (target_axis1 - curr_pos) / num_steps;
		double current_axis = curr_pos;
		for (int i = 0; i < num_steps; i++)
		{
			current_axis += step_size;
			if(is_x)
			{
				if (check_wall_collision(game, current_axis, axis2_fixed))
					break;
			}
			else
				if (check_wall_collision(game, axis2_fixed, current_axis))
					break;
			*p_axis1 = current_axis;
		}
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
		precise_wall_check(game, &game->player.pos.x, tmp.x, game->player.pos.y, true);
		precise_wall_check(game, &game->player.pos.y, tmp.y, game->player.pos.x, false);

	}
    else
    {
        tmp.x = game->player.pos.x - v2.x * move_speed;
        tmp.y = game->player.pos.y - v2.y * move_speed;
		precise_wall_check(game, &game->player.pos.x, tmp.x, game->player.pos.y, true);
		precise_wall_check(game, &game->player.pos.y, tmp.y, game->player.pos.x, false);
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