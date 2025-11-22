/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:55:19 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/22 13:12:34 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inits.h"

/**
 * @brief Initializes the main data structure and MiniLibX.
 *
 * Allocates memory for the data structure and initializes the MLX instance.
 *
 * @return Pointer to the initialized data structure, or NULL on failure.
 */
t_data	*init_data(void)
{
	t_data	*data;

	log_msg(INFO, __FILE__, __LINE__, "initializing data");
	data = log_calloc(1, sizeof(t_data), __FILE__, __LINE__);
	if (!data)
		return (NULL);
	log_msg(INFO, __FILE__, __LINE__, "initializing MiniLibX");
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
	{
		log_msg(ERROR, __FILE__, __LINE__, "failed to initialize MiniLibX");
		free(data);
		return (NULL);
	}
	return (data);
}
