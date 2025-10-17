/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:39:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/17 20:11:51 by vpoka            ###   ########.fr       */
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
	log_msg(INFO, __FILE__, __LINE__, "correct_file_extension()");
	if (correct_file_extension(file, ".cub"))
		return (1);
	//read file
}
