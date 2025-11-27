/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 16:57:13 by hasaliho          #+#    #+#             */
/*   Updated: 2025/11/21 17:06:47 by hasaliho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/render.h"

int	color_picker(t_game *game, int map_y, int map_x)
{
	char	c;

	c = game->map[map_y][map_x];
	if (c == '1')
		return (COLOR_GRAY);
	else
		return (COLOR_WHITE);
}

void	get_map_dimensions(t_game *game, int *width, int *height)
{
	int	w;
	int	h;
	int	current_row_len;

	w = 0;
	h = 0;
	while (game->map[h])
	{
		current_row_len = 0;
		while (game->map[h][current_row_len])
		{
			current_row_len++;
		}
		if (current_row_len > w)
			w = current_row_len;
		h++;
	}
	*width = w;
	*height = h;
}

double	get_tile_size(t_game *game)
{
	t_point	map_grid;
	t_point	ratio;
	t_point	minimap_max;
	double	tile_size;

	get_map_dimensions(game, &map_grid.x, &map_grid.y);
	minimap_max.x = game->mlx.width / 4;
	minimap_max.y = game->mlx.height / 4;
	ratio.x = (double)minimap_max.x / (double)map_grid.x;
	ratio.y = (double)minimap_max.y / (double)map_grid.y;
	tile_size = fmin(ratio.x, ratio.y);
	return (tile_size);
}
