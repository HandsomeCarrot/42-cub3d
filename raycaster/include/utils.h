/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 13:20:08 by hasaliho          #+#    #+#             */
/*   Updated: 2025/11/25 14:57:48 by hasaliho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

#include "types.h"

//hooks.c
int	key_handler(int keycode, void *param);
int close_handler(void *param);
void setup_hooks(t_game *game);

//cleanup.c
void cleanup_game(t_game *game);

//player.c
void	init_player(t_player *player, int grid_x, int grid_y, char orientation);

//utils.c
double get_time(void);
int	get_pixel_color(t_texture *tex, int x, int y);
void put_pixel(t_mlx *mlx, int x, int y, int color);
bool	check_wall(t_game *game, double x, double y);

#endif