/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:55:33 by hasaliho          #+#    #+#             */
/*   Updated: 2025/11/29 00:55:37 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "raycaster_types.h"
# include "raycaster_utils.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
#include "../parsing/parsing_types.h"

// --- Basic Colors ---
# define COLOR_WHITE 0xFFFFFF
# define COLOR_BLACK 0x000000
# define COLOR_RED 0xFF0000
# define COLOR_GREEN 0x00FF00
# define COLOR_BLUE 0x0000FF

// --- Secondary Colors ---
# define COLOR_YELLOW 0xFFFF00
# define COLOR_CYAN 0x00FFFF
# define COLOR_MAGENTA 0xFF00FF

// --- Shades & Tones ---
# define COLOR_GRAY 0x808080
# define COLOR_SILVER 0xC0C0C0
# define COLOR_MAROON 0x800000
# define COLOR_OLIVE 0x808000
# define COLOR_PURPLE 0x800080
# define COLOR_TEAL 0x008080
# define COLOR_NAVY 0x000080

// --- Brighter Tones ---
# define COLOR_ORANGE 0xFFA500
# define COLOR_PINK 0xFFC0CB
# define COLOR_BROWN 0xA52A2A

// --- Collision Value for wall_check ---
# define RADIUS 0.25
# define SAFE_STEP 0.2

// mlx_setup.c
int		init_mlx(t_game *game, t_map_data *config);

// texture_utils.c
int		load_all_textures(t_game *game, t_map_data *config);

// movement.c
void	new_pos(t_game *game);

// render.c
int		render(t_game *game);
int		render_loop(t_game *game);
void	init_ray(t_ray *ray, t_game *game, int x);
void	perform_dda(t_ray *ray, t_game *game);

// minimap.c
void	draw_minimap(t_game *game);
void	get_map_dimensions(t_game *game, int *width, int *height);
void	draw_player_triangle(t_game *game, double tile_size);
void	draw_minimap_rays(t_game *game, double tile_size);
int		color_picker(t_game *game, int map_y, int map_x);
double	get_tile_size(t_game *game);

// drawing_utils.c
void	draw_column(t_ray *ray, t_game *game, int x);

#endif
