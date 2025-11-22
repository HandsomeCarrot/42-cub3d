/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:05:56 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/22 13:13:31 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Checks if the map is playable (enclosed by walls).
 *
 * Iterates through the map layout and verifies that every floor tile ('0')
 * and player spawn is surrounded by valid neighbors.
 *
 * @param data Map data structure containing the layout.
 * @return 0 on success, 1 on failure.
 */
static int	check_map_playability(t_map_data *data)
{
	char	**map;
	int		x;
	int		y;

	if (!data)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	log_msg(DEBUG, __FILE__, __LINE__, "checking map integrity");
	map = data->map.layout;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if ((map[y][x] == '0' || is_player_spawn(map[y][x]))
				&& !has_valid_neighbors(x, y, data))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

/**
 * @brief Prints a string array to stdout (for debugging).
 *
 * @param array The null-terminated string array to print.
 */
static void	print_string_array(const char **array)
{
	int	line;

	if (!array)
	{
		log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM);
		return ;
	}
	line = 0;
	while (array[line])
	{
		printf("%s\n", array[line]);
		line++;
	}
}

/**
 * @brief Validates the parsed map layout.
 *
 * Locates the player and checks if the map is surrounded by walls.
 *
 * @param data Main data structure.
 * @return 0 on success, 1 on failure.
 */
int	parse_map_layout(t_data *data)
{
	int		error;

	if (!data)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	if (get_player_pos(&(data->map_data)))
		return (1);
	print_string_array((const char **)data->map_data.map.layout);
	error = check_map_playability(&data->map_data);
	return (error);
}
