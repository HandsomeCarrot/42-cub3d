/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:55:33 by hasaliho          #+#    #+#             */
/*   Updated: 2025/10/22 06:05:47 by hasaliho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RENDER_H
# define RENDER_H

#include <mlx.h>
#include <math.h>
#include "types.h"
#include "utils.h"
#include <stdbool.h>

//mlx_setup.c
void	put_pixel(t_mlx *mlx, int x, int y, int color);
int		init_mlx(t_game *game);

//render.c
int render(t_game *game);
int render_loop(t_game *game);


#endif
