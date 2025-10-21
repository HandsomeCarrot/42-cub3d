/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 14:32:38 by hasaliho          #+#    #+#             */
/*   Updated: 2025/10/21 14:39:26 by hasaliho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/render.h"

int render(t_game *game)
{
	int x;
	double camera_x;

	x = 0;
	while (x < game->mlx.width)
	{
		camera_x = 2.0 * x / (double)game->mlx.width - 1.0;
		printf("Column: %d, camera_x: %f\n", x, camera_x);
		x++;
	}
	return (1);
}
