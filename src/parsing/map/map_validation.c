/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:43:55 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/21 16:29:20 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @return true/false
 */
static bool	is_map_terrain(char c)
{
	if (ft_strchr(MAP_TERRAIN, c))
		return (true);
	return (false);
}

static bool	is_map_border(int x, int y, t_map_data *data)
{
	if (y <= 0 || y >= data->map.height - 1
		|| x <= 0 || x >= data->map.width - 1)
		return (true);
	return (false);
}

static bool	is_valid_neighbor(char c)
{
	if (is_map_terrain(c) || is_player_spawn(c))
		return (true);
	return (false);
}

bool	has_valid_neighbors(int x, int y, t_map_data *data)
{
	char	**map;

	map = data->map.layout;
	
	if (is_map_border(x, y, data)
		|| !is_valid_neighbor(map[y + 1][x])
		|| !is_valid_neighbor(map[y][x + 1])
		|| !is_valid_neighbor(map[y - 1][x])
		|| !is_valid_neighbor(map[y][x - 1]))
	{
		int log_fd = log_start(ERROR, __FILE__, __LINE__);
		if (log_fd >= 0)
		{
			ft_putstr_fd("in map on line ", log_fd);
			ft_putnbr_fd(y + 1, log_fd);
			ft_putstr_fd(", col ", log_fd);
			ft_putnbr_fd(x + 1, log_fd);
			ft_putendl_fd(": invalid map layout: map is not surrounded by walls", log_fd);
		}
		return (false);
	}
	return (true);
}
