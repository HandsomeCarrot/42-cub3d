/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:55:19 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/16 17:58:43 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cleanup.h"

void	main_cleanup(t_data *data)
{
	if (data)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data);
	}
}
