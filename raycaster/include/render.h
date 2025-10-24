/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:55:33 by hasaliho          #+#    #+#             */
/*   Updated: 2025/10/24 17:09:48 by hasaliho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RENDER_H
# define RENDER_H

#include <mlx.h>
#include <math.h>
#include "types.h"
#include "utils.h"
#include <stdbool.h>
#include <X11/keysym.h>
#include <X11/X.h>

// --- Basic Colors ---
#define COLOR_WHITE   0xFFFFFF
#define COLOR_BLACK   0x000000
#define COLOR_RED     0xFF0000
#define COLOR_GREEN   0x00FF00
#define COLOR_BLUE    0x0000FF

// --- Secondary Colors ---
#define COLOR_YELLOW  0xFFFF00
#define COLOR_CYAN    0x00FFFF
#define COLOR_MAGENTA 0xFF00FF

// --- Shades & Tones ---
#define COLOR_GRAY    0x808080
#define COLOR_SILVER  0xC0C0C0
#define COLOR_MAROON  0x800000
#define COLOR_OLIVE   0x808000
#define COLOR_PURPLE  0x800080
#define COLOR_TEAL    0x008080
#define COLOR_NAVY    0x000080

// --- Brighter Tones ---
#define COLOR_ORANGE  0xFFA500
#define COLOR_PINK    0xFFC0CB
#define COLOR_BROWN   0xA52A2A

//tile_size
#define TILE_SIZE 20

//mlx_setup.c
void	put_pixel(t_mlx *mlx, int x, int y, int color);
int		init_mlx(t_game *game);

//render.c
int		render(t_game *game);
int		render_loop(t_game *game);

//minimap.c
void	draw_minimap(t_game *game);
void	draw_player_on_minimap(t_game *game);


#endif
