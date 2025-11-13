/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_layout.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:05:56 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/13 15:51:38 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
