/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 09:13:56 by hasaliho          #+#    #+#             */
/*   Updated: 2025/11/25 14:07:47 by hasaliho         ###   ########.fr       */
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

void	perform_rot(t_game *game, double angle)
{
	double	tmp_vec;

	tmp_vec = game->player.look_dir.x;
	game->player.look_dir.x = tmp_vec * cos(angle) - game->player.look_dir.y
		* sin(angle);
	game->player.look_dir.y = tmp_vec * sin(angle) + game->player.look_dir.y
		* cos(angle);
	tmp_vec = game->player.plane.x;
	game->player.plane.x = tmp_vec * cos(angle) - game->player.plane.y
		* sin(angle);
	game->player.plane.y = tmp_vec * sin(angle) + game->player.plane.y
		* cos(angle);
}

void	precise_wall_check(t_game *game, double *p_axis, double target,
	bool is_x)
{
	double	dist;
	int		num_steps;
	double	step_size;
	double	current;
	int		i;

	dist = fabs(target - *p_axis);
	if (dist < 0.0001)
		return ;
	num_steps = (int)ceil(dist / SAFE_STEP);
	step_size = (target - *p_axis) / num_steps;
	current = *p_axis;
	i = 0;
	while (i < num_steps)
	{
		current += step_size;
		if (is_x && check_wall_collision(game, current, game->player.pos.y))
			break ;
		if (!is_x && check_wall_collision(game, game->player.pos.x, current))
			break ;
		*p_axis = current;
		i++;
	}
}

void	perform_move(t_game *game, char op, t_vector v2)
{
	t_vector	tmp;
	double		move_speed;

	move_speed = game->player.speed;
	move_speed = move_speed * game->player.delta_time;
	if (op == '+')
	{
		tmp.x = game->player.pos.x + v2.x * move_speed;
		tmp.y = game->player.pos.y + v2.y * move_speed;
		precise_wall_check(game, &game->player.pos.x, tmp.x,
			true);
		precise_wall_check(game, &game->player.pos.y, tmp.y,
			false);
	}
	else
	{
		tmp.x = game->player.pos.x - v2.x * move_speed;
		tmp.y = game->player.pos.y - v2.y * move_speed;
		precise_wall_check(game, &game->player.pos.x, tmp.x,
			true);
		precise_wall_check(game, &game->player.pos.y, tmp.y,
			false);
	}
}

void	new_pos(t_game *game)
{
	double	rot_speed;

	if (game->keys.shift)
		game->player.speed = 12.0;
	else
		game->player.speed = 5.0;
	rot_speed = 3.0 * game->player.delta_time;
	if (game->keys.move_forward)
		perform_move(game, '+', game->player.look_dir);
	if (game->keys.move_back)
		perform_move(game, '-', game->player.look_dir);
	if (game->keys.strafe_right)
		perform_move(game, '+', game->player.plane);
	if (game->keys.strafe_left)
		perform_move(game, '-', game->player.plane);
	if (game->keys.rotate_left)
		perform_rot(game, -rot_speed);
	if (game->keys.rotate_right)
		perform_rot(game, rot_speed);
}
