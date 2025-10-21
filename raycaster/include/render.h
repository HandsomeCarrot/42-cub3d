/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:55:33 by hasaliho          #+#    #+#             */
/*   Updated: 2025/10/21 13:33:04 by hasaliho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef RENDER_H
# define RENDER_H

#include <mlx.h>
#include "types.h"
#include "utils.h"

void	put_pixel(t_mlx *mlx, int x, int y, int color);
int		init_mlx(t_game *game);


#endif
