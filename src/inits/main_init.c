/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:55:19 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/16 20:13:13 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inits.h"

t_data	*init_data(void)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		log_msg(ERROR, __FILE__, __LINE__, "memory allocation failed\n");
	else
	{
		data->mlx_ptr = mlx_init();
		if (!data->mlx_ptr)
		{
			log_msg(ERROR, __FILE__, __LINE__, "failed to initialize mlx\n");
			free(data);
			return (NULL);
		}
	}
	return (data);
}
