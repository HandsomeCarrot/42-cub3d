/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_layout.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:05:56 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/11 18:29:52 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @return true/false
 */
static bool	is_player_spawn(char c)
{
	if (ft_strchr(PLAYER_SPAWN, c))
		return (true);
	return (false);
}

/**
 * @return 0 on success, other on error
 */
static int	save_player_pos(int y, int x, char orientation, t_player *player)
{
	if (!player)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	log_msg(DEBUG, __FILE__, __LINE__, "saving player position data");
	if (player->found)
	{
		log_msg(ERROR, __FILE__, __LINE__, "multiple player spawns defined");
		return (1);
	}
	player->found = 1;
	player->posY = y;
	player->posX = x;
	player->orientation = orientation;
	return (0);
}

/**
 * @return 0 on success, other on error
 */
static int	get_player_pos(t_data *data)
{
	char	**map;
	int		posY;
	int		posX;

	if (!data)
		return (log_msg(WARNING, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	log_msg(DEBUG, __FILE__, __LINE__, "searching for player spawn");
	map = data->map_data.map;
	posY = 0;
	while(map[posY])
	{
		posX = 0;
		while (map[posY][posX])
		{
			if (is_player_spawn(map[posY][posX])
				&& save_player_pos(posY, posX, map[posY][posX],
					&data->map_data.player))
					return (1);
			posX++;
		}
		posY++;
	}
	if (!data->map_data.player.found)
		return (log_msg(ERROR, __FILE__, __LINE__, "no player spawn found"), 1);
	return (0);
}

/**
 * @return 0 on success, other on failure
 */
static int	check_map_playability(char **map)
{
	(void)map;
	return (0);
}

static char	**copy_string_array(const char **array)
{
	char	**array_copy;
	size_t	size;

	if (!array)
		return (NULL);
	size = 0;
	while (array[size])
		size++;
	array_copy = log_calloc(size + 1, sizeof(char *), __FILE__, __LINE__);
	if (!array_copy)
		return (NULL);
	size = 0;
	while (array[size])
	{
		array_copy[size] = ft_strdup(array[size]);
		if (!array_copy[size])
		{
			free_string_array(&array_copy);
			return (NULL);
		}
		size++;
	}
	return (array_copy);
}

int	parse_map_layout(t_data *data) //TODO: finish
{
	char	**map;
	int		error;

	if (!data)
		return(log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	if (get_player_pos(data))
		return (1);
	map = copy_string_array((const char **)data->map_data.map);
	if (!map)
		return (1);
	error = check_map_playability(map);
	free_string_array(&map);
	return (error);
}
