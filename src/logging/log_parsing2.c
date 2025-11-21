/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_parsing2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 18:26:41 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/21 19:52:40 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logging.h"

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
	ft_putstr_fd("missing texture identifier(s): ", log_fd);
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

void	log_invalid_map_line(int row, const char *line, int pos)
{
	int	log_fd;

	log_fd = log_start(ERROR, __FILE__, __LINE__);
	if (log_fd >= 0)
	{
		ft_putstr_fd("in map on line ", log_fd);
		ft_putnbr_fd(row, log_fd);
		ft_putstr_fd(":", log_fd);
		ft_putnbr_fd(pos + 1, log_fd);
		ft_putstr_fd(": invalid character in map: '", log_fd);
		ft_putchar_fd(line[pos], log_fd);
		ft_putendl_fd("'", log_fd);
	}
}

void	log_multiple_player_spawns(int y, int x)
{
	int	log_fd;

	log_fd = log_start(ERROR, __FILE__, __LINE__);
	if (log_fd >= 0)
	{
		ft_putstr_fd("in map layout: multiple player spawns defined", log_fd);
		ft_putstr_fd(" (found at line ", log_fd);
		ft_putnbr_fd(y + 1, log_fd);
		ft_putstr_fd(":", log_fd);
		ft_putnbr_fd(x + 1, log_fd);
		ft_putendl_fd(")", log_fd);
	}
}
