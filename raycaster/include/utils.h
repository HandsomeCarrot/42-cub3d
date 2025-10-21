/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 13:20:08 by hasaliho          #+#    #+#             */
/*   Updated: 2025/10/21 15:19:05 by hasaliho         ###   ########.fr       */
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

#endif