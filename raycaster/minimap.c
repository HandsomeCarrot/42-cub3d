/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:06:00 by hasaliho          #+#    #+#             */
/*   Updated: 2025/10/28 12:36:56 by hasaliho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/render.h"

int color_picker(t_game *game, int map_y, int map_x)
{
    char c = game->map[map_y][map_x];
    if(c == '1')
        return COLOR_GRAY;
    else
        return COLOR_WHITE;
}

void get_map_dimensions(t_game *game, int *width, int *height)
{
    int w = 0;
    int h = 0;
    int current_row_len;

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
	t_point map_grid;
	t_point ratio;
	t_point minimap_max;


	get_map_dimensions(game, &map_grid.x, &map_grid.y);

	minimap_max.x = game->mlx.width / 4;
	minimap_max.y = game->mlx.height / 4;

	ratio.x = (double)minimap_max.x / (double)map_grid.x;
	ratio.y = (double)minimap_max.y / (double)map_grid.y;

	double tile_size = fmin(ratio.x, ratio.y);
	return tile_size;
}

void draw_minimap(t_game *game)
{

int map_x;
int map_y = 0;
int pixel_x = 0;
int pixel_y = 0;
int screen_y;
int screen_x;
double tile_size = get_tile_size(game);
    while (game->map[map_y])
    {
        map_x = 0;
        while (game->map[map_y][map_x])
        {
            pixel_y = 0;
            while (pixel_y < (int)tile_size) 
            {
                pixel_x = 0;
                screen_y = map_y * tile_size + pixel_y;
                while (pixel_x < (int)tile_size)
                {
                    screen_x = map_x * tile_size + pixel_x;
                    int color = color_picker(game, map_y, map_x);
                    put_pixel(&game->mlx, screen_x, screen_y, color);
                    pixel_x++;
                }
                pixel_y++;
            }
            map_x++;
        }
        map_y++;
    }
}

void draw_player_on_minimap(t_game *game)
{
	double tile_size = get_tile_size(game);
    int screen_x = (int)(game->player.pos.x * tile_size);
    int screen_y = (int)(game->player.pos.y * tile_size);
    int y = 0;
    int x = 0;
    int size = 3;
    while(y < size)
    {
        x = 0;
        while (x < size)
        {
            put_pixel(&game->mlx, (screen_x - 1) + x, (screen_y - 1) + y, COLOR_TEAL);
            x++;
        }
        y++;
    }
}