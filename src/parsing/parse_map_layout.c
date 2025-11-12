/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_layout.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:05:56 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/12 23:27:10 by vpoka            ###   ########.fr       */
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
 * @return true/false
 */
static bool	is_map_terrain(char c)
{
	if (ft_strchr(MAP_TERRAIN, c))
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
		log_msg(ERROR, __FILE__, __LINE__, "multiple player spawns defined");
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
static int	get_player_pos(t_map_data *data)
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
		return (log_msg(ERROR, __FILE__, __LINE__, "no player spawn found"), 1);
	return (0);
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

static bool	has_valid_neighbors(int x, int y, t_map_data *data)
{
	char	**map;

	map = data->map.layout;
	
	if (is_map_border(x, y, data)
		|| !is_valid_neighbor(map[y + 1][x])
		|| !is_valid_neighbor(map[y][x + 1])
		|| !is_valid_neighbor(map[y - 1][x])
		|| !is_valid_neighbor(map[y][x - 1]))
	{
		log_msg(ERROR, __FILE__, __LINE__,
			"invalid map layout: map is not surrounded by walls");
		return (false);
	}
	return (true);
}

/**
 * @return 0 on success, other on failure
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

int	parse_map_layout(t_data *data) //TODO: finish
{
	int		error;

	if (!data)
		return(log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	if (get_player_pos(&(data->map_data)))
		return (1);
	print_string_array((const char**)data->map_data.map.layout);
	error = check_map_playability(&data->map_data);
	return (error);
}
