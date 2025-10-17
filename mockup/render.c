/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 07:13:26 by hasaliho          #+#    #+#             */
/*   Updated: 2025/10/17 07:13:48 by hasaliho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

void	draw_gradient(t_game *g)
{
	int	x;
	int	y;
	int	gray;

	x = 0;
	while (x < g->mlx.win_w)
	{
		y = 0;
		while (y < g->mlx.win_h)
		{
			gray = (y * 255) / g->mlx.win_h;
			put_pixel(&g->mlx, x, y, (gray << 16) | (gray << 8) | gray);
			y++;
		}
		x++;
	}
}
