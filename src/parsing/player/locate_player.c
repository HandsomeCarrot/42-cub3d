/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_location.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:50:33 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/21 20:14:18 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @return true/false
 */
bool	is_player_spawn(char c)
{
	if (ft_strchr(PLAYER_SPAWN, c))
		return (true);
	return (false);
}

/**
 * @return 0 on success, other on error
 */
static int	save_player_pos(int y, int x, t_map_data *data)
{
	int	log_fd;

	if (!data)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	if (data->player.found)
	{
		log_multiple_player_spawns(data->map.start_line + y + 1, x);
		return (1);
	}
	data->player.found = 1;
	data->player.pos_y = y;
	data->player.pos_x = x;
	data->player.orientation = data->map.layout[y][x];
	log_fd = log_start(DEBUG, __FILE__, __LINE__);
	if (log_fd >= 0)
		printf("found player position: [%d,%d|%c]\n", x + 1, y + 1,
			data->player.orientation);
	return (0);
}

/**
 * @return 0 on success, other on error
 */
int	get_player_pos(t_map_data *data)
{
	char	**map;
	int		pos_y;
	int		pos_x;

	if (!data)
		return (log_msg(WARNING, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	log_msg(DEBUG, __FILE__, __LINE__, "searching for player spawn");
	map = data->map.layout;
	pos_y = 0;
	while (map[pos_y])
	{
		pos_x = 0;
		while (map[pos_y][pos_x])
		{
			if (is_player_spawn(map[pos_y][pos_x])
				&& save_player_pos(pos_y, pos_x, data))
				return (1);
			pos_x++;
		}
		pos_y++;
	}
	if (!data->player.found)
		return (log_msg(ERROR, __FILE__, __LINE__,
				"in map layout: missing player spawn"), 1);
	return (0);
}
