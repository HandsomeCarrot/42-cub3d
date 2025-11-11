/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:31:25 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/11 17:01:55 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_player
{
	int		found;
	int		posX;
	int		posY;
	char	orientation;
}				t_player;

typedef struct s_map_data
{
	char	**map;
	char	*north_wall_image;
	char	*east_wall_image;
	char	*south_wall_image;
	char	*west_wall_image;
	int		floor_color;
	int		ceiling_color;
	t_player	player;
}				t_map_data;

typedef struct s_data
{
	void		*mlx_ptr;
	t_map_data	map_data;
}				t_data;

#endif /* STRUCTS_H */
