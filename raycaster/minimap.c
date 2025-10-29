/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 17:06:00 by hasaliho          #+#    #+#             */
/*   Updated: 2025/10/29 08:12:06 by hasaliho         ###   ########.fr       */
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
            int color = color_picker(game, map_y, map_x);
            pixel_y = 0;
            while (pixel_y < (int)tile_size) 
            {
                pixel_x = 0;
                screen_y = map_y * tile_size + pixel_y;
                while (pixel_x < (int)tile_size)
                {
                    screen_x = map_x * tile_size + pixel_x;
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

/*
** Draws a line from point p1 to p2 using a simple DDA algorithm.
** We'll need a t_point struct, or just pass (x1, y1, x2, y2).
** Let's assume you have a t_point struct:
** typedef struct s_point { int x; int y; } t_point;
*/
void draw_line(t_mlx *mlx, t_point p1, t_point p2, int color)
{
    double  delta_x;
    double  delta_y;
    int     steps;
    double  x;
    double  y;
    double  x_inc;
    double  y_inc;

    delta_x = p2.x - p1.x;
    delta_y = p2.y - p1.y;

    // Figure out which is the longer side (dx or dy)
    if (fabs(delta_x) > fabs(delta_y))
        steps = fabs(delta_x);
    else
        steps = fabs(delta_y);

    // Calculate the increment for each step
    x_inc = delta_x / (double)steps;
    y_inc = delta_y / (double)steps;

    // Start at the first point
    x = p1.x;
    y = p1.y;
    
    // Put a pixel for each step
    int i = 0;
    while (i <= steps)
    {
        put_pixel(mlx, (int)x, (int)y, color); // Cast to int for put_pixel
        x += x_inc;
        y += y_inc;
        i++;
    }
}

// Replaces draw_player_on_minimap
void draw_player_triangle(t_game *game, double tile_size)
{
    t_point p1, p2, p3; // The 3 final screen points
    
    // 1. Define local points (relative to 1 map tile)
    //    These values are much smaller (fractions of a tile).
    double p1_local_x = 0;   double p1_local_y = 0.5;  // Tip: half a tile forward
    double p2_local_x = -0.3;  double p2_local_y = -0.3; // Back-left
    double p3_local_x = 0.3;   double p3_local_y = -0.3; // Back-right

    // 2. Get player's direction vectors
    double fwd_x = game->player.look_dir.x;
    double fwd_y = game->player.look_dir.y;
    double right_x = game->player.plane.x;
    double right_y = game->player.plane.y;

    // 3. Rotate the 3 points (this logic stays the same)
    double p1_world_x = p1_local_x * right_x + p1_local_y * fwd_x;
    double p1_world_y = p1_local_x * right_y + p1_local_y * fwd_y;
    
    double p2_world_x = p2_local_x * right_x + p2_local_y * fwd_x;
    double p2_world_y = p2_local_x * right_y + p2_local_y * fwd_y;

    double p3_world_x = p3_local_x * right_x + p3_local_y * fwd_x;
    double p3_world_y = p3_local_x * right_y + p3_local_y * fwd_y;

    // 4. Add player's position and scale to minimap (this logic stays the same)
    p1.x = (int)((game->player.pos.x + p1_world_x) * tile_size);
    p1.y = (int)((game->player.pos.y + p1_world_y) * tile_size);

    p2.x = (int)((game->player.pos.x + p2_world_x) * tile_size);
    p2.y = (int)((game->player.pos.y + p2_world_y) * tile_size);

    p3.x = (int)((game->player.pos.x + p3_world_x) * tile_size);
    p3.y = (int)((game->player.pos.y + p3_world_y) * tile_size);

    // 5. Draw the 3 lines (this logic stays the same)
    draw_line(&game->mlx, p1, p2, COLOR_RED);
    draw_line(&game->mlx, p2, p3, COLOR_RED);
    draw_line(&game->mlx, p3, p1, COLOR_RED);
}

/*
** Casts rays and draws them on the minimap.
** This logic is copied from your render() function.
*/
void draw_minimap_rays(t_game *game, double tile_size)
{
    t_ray   ray;
    t_point player_pos;
    t_point hit_pos;
    int     x;

    // 1. Get player's minimap screen position
    player_pos.x = (int)(game->player.pos.x * tile_size);
    player_pos.y = (int)(game->player.pos.y * tile_size);

    // 2. Loop through screen columns, but skip every 10
    //    to only draw a few rays.
    x = 0;
    while (x < game->mlx.width)
    {
        // 3. Cast a ray (same as in your render() function)
        init_ray(&ray, game, x);
        perform_dda(&ray, game);

        // 4. Calculate the wall hit position in WORLD coordinates
        double hit_world_x;
        double hit_world_y;
        
        hit_world_x = game->player.pos.x + ray.perp_wall_dist * ray.dir.x;
        hit_world_y = game->player.pos.y + ray.perp_wall_dist * ray.dir.y;
        
        // 5. Scale hit position to SCREEN coordinates
        hit_pos.x = (int)(hit_world_x * tile_size);
        hit_pos.y = (int)(hit_world_y * tile_size);

        // 6. Draw the ray
        draw_line(&game->mlx, player_pos, hit_pos, COLOR_YELLOW);
        
        x += 30; // Skip 30 pixels for the next ray
    }
}