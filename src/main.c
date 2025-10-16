/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:26:09 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/16 17:38:27 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static t_data	*init_data(void)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		log_msg(ERROR, __FILE__, __LINE__, "memory allocation failed");
	else
	{
		data->mlx_ptr = mlx_init();
		if (!data->mlx_ptr)
		{
			log_msg(ERROR, __FILE__, __LINE__, "failed to initialize mlx");
			free(data);
			return (NULL);
		}
	}
	return (data);
}

static void	main_cleanup(t_data *data)
{
	if (data)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data);
	}
}

int	main(void)
{
	t_data	*data;

	data = init_data();
	if (!data)
		return (1);
	main_cleanup(data);
	return (0);
}
