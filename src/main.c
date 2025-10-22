/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:26:09 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/22 21:04:32 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	log_msg(INFO, __FILE__, __LINE__, "executing cub3d");
	data = init_data();
	if (!data)
		return (1);
	if (parse(argc, argv, data))
		return (main_cleanup(data), 1);
	return (main_cleanup(data), 0);
}
