/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_neighbors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 15:43:55 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/23 18:50:31 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/parsing.h"

/**
 * @brief Checks if a character represents valid map terrain (0 or 1).
 *
 * @param c The character to check.
 * @return true if valid terrain, false otherwise.
 */
static bool	is_map_terrain(char c)
{
	if (ft_strchr(MAP_TERRAIN, c))
		return (true);
	return (false);
}

/**
 * @brief Checks if the given coordinates are on the map border.
 *
 * @param x The x-coordinate.
 * @param y The y-coordinate.
 * @param data The map data structure.
 * @return true if on border, false otherwise.
 */
static bool	is_map_border(int x, int y, t_map_data *data)
{
	if (y <= 0 || y >= data->map.height - 1
		|| x <= 0 || x >= data->map.width - 1)
		return (true);
	return (false);
}

/**
 * @brief Checks if a character is a valid neighbor for a floor tile.
 *
 * Valid neighbors are walls (1), floors (0), or player spawns.
 *
 * @param c The character to check.
 * @return true if valid neighbor, false otherwise.
 */
static bool	is_valid_neighbor(char c)
{
	if (is_map_terrain(c) || is_player_spawn(c))
		return (true);
	return (false);
}

/**
 * @brief Verifies that a floor tile has valid neighbors.
 *
 * Checks the 4 surrounding neighbors (up, down, left, right).
 *
 * @param x The x-coordinate of the tile.
 * @param y The y-coordinate of the tile.
 * @param data The map data structure.
 * @return true if valid, false otherwise.
 */
bool	has_valid_neighbors(int x, int y, t_map_data *data)
{
	char	**map;
	int		log_fd;

	map = data->map.layout;
	if (is_map_border(x, y, data)
		|| !is_valid_neighbor(map[y + 1][x])
		|| !is_valid_neighbor(map[y][x + 1])
		|| !is_valid_neighbor(map[y - 1][x])
		|| !is_valid_neighbor(map[y][x - 1]))
	{
		log_fd = log_start(ERROR, __FILE__, __LINE__);
		if (log_fd >= 0)
		{
			ft_putstr_fd("map: line ", log_fd);
			ft_putnbr_fd(data->map.start_line + y + 1, log_fd);
			ft_putstr_fd(":", log_fd);
			ft_putnbr_fd(x + 1, log_fd);
			ft_putstr_fd(": map layout", log_fd);
			ft_putendl_fd(": map is not surrounded by walls", log_fd);
		}
		return (false);
	}
	return (true);
}
