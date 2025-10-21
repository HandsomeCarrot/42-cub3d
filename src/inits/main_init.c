/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:55:19 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/21 19:39:26 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inits.h"

t_data	*init_data(void)
{
	t_data	*data;

	data = log_calloc(1, sizeof(t_data), __FILE__, __LINE__);
	if (!data)
		return (NULL);
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
	{
		log_msg(ERROR, __FILE__, __LINE__, "failed to initialize mlx\n");
		free(data);
		return (NULL);
	}
	return (data);
}
