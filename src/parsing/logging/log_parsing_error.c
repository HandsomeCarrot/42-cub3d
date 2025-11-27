/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_parsing_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 18:26:41 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/23 18:52:28 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/parsing.h"

/**
 * @brief Logs which texture identifiers are missing
 *
 * @param ids Array of texture identifiers to check
 */
void	log_missing_ids(t_map_id *ids)
{
	int	id_pos;
	int	log_fd;

	if (!ids)
		return ;
	log_fd = log_start(ERROR, __FILE__, __LINE__);
	if (log_fd < 0)
		return ;
	ft_putstr_fd("map: missing texture identifier(s): ", log_fd);
	id_pos = 0;
	while (ids[id_pos].id)
	{
		if (!ids[id_pos].found)
		{
			ft_putstr_fd("'", log_fd);
			ft_putstr_fd((char *)ids[id_pos].id, log_fd);
			ft_putstr_fd("' ", log_fd);
		}
		id_pos++;
	}
	ft_putendl_fd("", log_fd);
}

/**
 * @brief Logs an error for an invalid file extension.
 *
 * @param file The filename that is invalid.
 * @param extension The expected extension.
 */
void	log_invalid_file(const char *file, const char *extension)
{
	int	log_fd;

	log_fd = log_start(ERROR, __FILE__, __LINE__);
	if (log_fd >= 0)
	{
		ft_putstr_fd("invalid file name '", log_fd);
		ft_putstr_fd((char *)file, log_fd);
		ft_putstr_fd("': unsupported file extension (expected: ", log_fd);
		ft_putstr_fd((char *)extension, log_fd);
		ft_putendl_fd(")", log_fd);
	}
}

/**
 * @brief Logs an error for an invalid character in the map.
 *
 * @param row The line number in the map.
 * @param line The content of the line.
 * @param pos The position of the invalid character.
 */
void	log_invalid_map_line(int row, const char *line, int pos)
{
	int	log_fd;

	log_fd = log_start(ERROR, __FILE__, __LINE__);
	if (log_fd >= 0)
	{
		ft_putstr_fd("map: line ", log_fd);
		ft_putnbr_fd(row, log_fd);
		ft_putstr_fd(":", log_fd);
		ft_putnbr_fd(pos + 1, log_fd);
		ft_putstr_fd(": map layout: invalid character: '", log_fd);
		ft_putchar_fd(line[pos], log_fd);
		ft_putendl_fd("'", log_fd);
	}
}

/**
 * @brief Logs an error when multiple player spawns are found.
 *
 * @param y The y-coordinate (line number) of the duplicate spawn.
 * @param x The x-coordinate (column number) of the duplicate spawn.
 */
void	log_multiple_player_spawns(int y, int x)
{
	int	log_fd;

	log_fd = log_start(ERROR, __FILE__, __LINE__);
	if (log_fd >= 0)
	{
		ft_putstr_fd("map: line ", log_fd);
		ft_putnbr_fd(y + 1, log_fd);
		ft_putstr_fd(":", log_fd);
		ft_putnbr_fd(x + 1, log_fd);
		ft_putendl_fd(": map layout: multiple player spawns defined", log_fd);
	}
}
