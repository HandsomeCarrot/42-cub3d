/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:26:06 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/16 16:54:52 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "libft.h"
# include "logging.h"
# include "parsing.h"
# include <mlx.h>
# include <stdio.h>

typedef struct s_data
{
	void		*mlx_ptr;
	t_map_data	map_data;
}				t_data;

#endif
