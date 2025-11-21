/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_location.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:50:33 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/21 17:38:17 by vpoka            ###   ########.fr       */
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
		log_fd = log_start(ERROR, __FILE__, __LINE__);
		if (log_fd >= 0)
		{
			ft_putstr_fd("in map layout: multiple player spawns defined (found at line ", log_fd);
			ft_putnbr_fd(y + 1, log_fd);
			ft_putstr_fd(":", log_fd);
			ft_putnbr_fd(x + 1, log_fd);
			ft_putendl_fd(")", log_fd);
		}
		return (1);
	}
	data->player.found = 1;
	data->player.posY = y;
	data->player.posX = x;
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
	int		posY;
	int		posX;

	if (!data)
		return (log_msg(WARNING, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	log_msg(DEBUG, __FILE__, __LINE__, "searching for player spawn");
	map = data->map.layout;
	posY = 0;
	while(map[posY])
	{
		posX = 0;
		while (map[posY][posX])
		{
			if (is_player_spawn(map[posY][posX])
				&& save_player_pos(posY, posX, data))
					return (1);
			posX++;
		}
		posY++;
	}
	if (!data->player.found)
		return (log_msg(ERROR, __FILE__, __LINE__, "in map layout: missing player spawn"), 1);
	return (0);
}
