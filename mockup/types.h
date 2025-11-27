/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasaliho <hasaliho@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:56:01 by hasaliho          #+#    #+#             */
/*   Updated: 2025/10/17 15:15:11 by hasaliho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef struct s_map
{
	int			width;
	int			height;
	const char	**grid;
}	t_map;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}	t_player;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			win_w;
	int			win_h;
}	t_mlx;

typedef struct s_game
{
	t_mlx		mlx;
	t_map		map;
	t_player	player;
}	t_game;

void	draw_gradient(t_game *g);
void	put_pixel(t_mlx *mlx, int x, int y, int color);
void	cast_debug_ray(t_game *g, int x);
void	render_frame(t_game *g);

#endif
