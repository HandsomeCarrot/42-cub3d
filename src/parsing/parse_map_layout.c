/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_layout.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:05:56 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/12 17:11:00 by vpoka            ###   ########.fr       */
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
	int	log_fd;

	if (!player)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	if (player->found)
	{
		log_msg(ERROR, __FILE__, __LINE__, "multiple player spawns defined");
		return (1);
	}
	log_fd = log_start(DEBUG, __FILE__, __LINE__);
	if (log_fd >= 0)
	{
		ft_putstr_fd("found player position: [", log_fd);
		ft_putnbr_fd(y, log_fd);
		ft_putchar_fd(',', log_fd);
		ft_putnbr_fd(x, log_fd);
		ft_putchar_fd(',', log_fd);
		ft_putchar_fd(orientation, log_fd);
		ft_putendl_fd("]", log_fd);
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

static bool	is(char c)
{
	if (c == '0' || c == '1' || is_player_spawn(c))
		return (true);
	return (false);
}

static bool	cross_check(int x, int y, t_map_data *data)
{
	char	**map;

	map = data->map.layout;
	if (y <= 0 || y >= (data->map.height - 1))
		return (false);
	else if (x <= 0 || x >= data->map.width - 1)
		return (false);
	else if (!is(map[y + 1][x]) || !is(map[y][x + 1]) || !is(map[y - 1][x]) || !is(map[y][x - 1]))
		return (false);
	return (true);
}

/**
 * @return 0 on success, other on failure
 */
static int	check_map_playability(t_map_data *data)//TODO: iterative flood fill
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
			if (map[y][x] == '0' || is_player_spawn(map[y][x]))
			{
				if (!cross_check(x, y, data))
				{
					log_line_error(y + 1, "invalid map", __FILE__, __LINE__);
					return (1);
				}
			}
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
		ft_putendl_fd((char *)array[line], STDOUT_FILENO);
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
