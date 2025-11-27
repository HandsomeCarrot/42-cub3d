/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:59:07 by hasaliho          #+#    #+#             */
/*   Updated: 2025/11/27 11:30:47 by hasaliho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/render.h"

double	get_time(void)
{
	struct timeval	tv;

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

int	get_pixel_color(t_texture *tex, int x, int y)
{
	int	offset;

	offset = y * tex->line_length + x * tex->bytes_per_pixel;
	return (*(int *)(tex->img_data + offset));
}

bool	check_wall(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_x < 0)
		return (true);
	if (game->map[map_y] == NULL)
		return (true);
	if (game->map[map_y][map_x] == '\0')
		return (true);
	if (game->map[map_y][map_x] == '1')
		return (true);
	return (false);
}
