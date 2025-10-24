/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:06:00 by hasaliho          #+#    #+#             */
/*   Updated: 2025/10/24 17:07:53 by hasaliho         ###   ########.fr       */
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

void draw_minimap(t_game *game)
{
int map_y = 0;
int pixel_x = 0;
int pixel_y = 0;
    while (game->map[map_y])
    {
        int map_x = 0;
        while (game->map[map_y][map_x])
        {
            pixel_y = 0;
            while (pixel_y < TILE_SIZE) 
            {
                pixel_x = 0;
                int screen_y = map_y * TILE_SIZE + pixel_y;
                while (pixel_x < TILE_SIZE)
                {
                    int screen_x = map_x * TILE_SIZE + pixel_x;
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
    int screen_x = (int)game->player.pos.x * TILE_SIZE;
    int screen_y = (int)game->player.pos.y * TILE_SIZE;
    int pixel_x = 0;
    int pixel_y = 0;

    while (pixel_x < TILE_SIZE)
    {
        pixel_y = 0;
        screen_x = game->player.pos.x * TILE_SIZE + pixel_x;
        while (pixel_y < TILE_SIZE)
        {
            screen_y = game->player.pos.y * TILE_SIZE + pixel_y;
            put_pixel(&game->mlx, screen_x, screen_y, COLOR_MAGENTA);
            pixel_y++;
        }
        pixel_x++;
    }    
}