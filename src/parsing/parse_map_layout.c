/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_layout.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:05:56 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/11 19:56:11 by vpoka            ###   ########.fr       */
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
				&& save_player_pos(posY, posX, map[posY][posX],
					&(data->player)))
					return (1);
			posX++;
		}
		posY++;
	}
	if (!data->player.found)
		return (log_msg(ERROR, __FILE__, __LINE__, "no player spawn found"), 1);
	return (0);
}

/**
 * @return 0 on success, other on failure
 */
static int	check_map_playability(char **map, t_map_data *data)//TODO: first have to fix map, so that all lines have same width
{
	int	down, up, left, right;

	if (!map || !data)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	log_msg(DEBUG, __FILE__, __LINE__, "checking map integrity");
	down = data->player.posY;
	left = data->player.posX;
	//check down
	while (down >= 0 && map[down])
	{
		//check left
		while (left >= 0 && map[down][left])
		{
			//check up
			up = down;
			while (map[up][left])
			{
				//check right
				right = left;
				while (map[up][right])
				{
					if (map[up][right] == '0')
						map[up][right] = '1';
					right++;
				}
				up++;
			}
			left--;
		}
		down--;
	}
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
		ft_putendl_fd((char *)array[line], STDOUT_FILENO);
		line++;
	}
}

int	parse_map_layout(t_data *data) //TODO: finish
{
	char	**map;
	int		error;

	if (!data)
		return(log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	if (get_player_pos(&(data->map_data)))
		return (1);
	map = copy_string_array((const char **)data->map_data.map.layout);
	if (!map)
		return (1);
	error = check_map_playability(map, &data->map_data);
	print_string_array((const char**)map);
	free_string_array(&map);
	print_string_array((const char**)data->map_data.map.layout);
	return (error);
}
