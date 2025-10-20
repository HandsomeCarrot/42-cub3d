/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:39:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/20 21:21:33 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief reads map data out of map file
 *
 * @return 0 on success, 1 on error
 */
int	parse_map_file(char *file, t_data *data)
{
	int	fd;

	log_msg(INFO, __FILE__, __LINE__, "correct_file_extension()");
	if (correct_file_extension(file, ".cub"))
		return (1);
	fd = open_file_read(file);
	if (fd < 0)
		return (1);
	get_next_line(fd);
}
