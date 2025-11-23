/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:59:07 by hasaliho          #+#    #+#             */
/*   Updated: 2025/11/21 21:47:55 by hasaliho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/render.h"

double get_time(void)
{
    struct timeval tv;
    
    gettimeofday(&tv, NULL);
    return (tv.tv_sec + tv.tv_usec / 1000000.0);
}

void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	int	offset;

	if (x < 0 || x >= mlx->width || y < 0 || y >= mlx->height)
		return ;
	offset = (y * mlx->line_length + x * mlx->bytes_per_pixel);
	*(unsigned int *)(mlx->img_data + offset) = color;
}
