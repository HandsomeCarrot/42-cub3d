/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:26:06 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/15 12:03:18 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "cleanup.h"
# include "definitions.h"
# include "inits.h"
# include "libft.h"
# include "logging.h"
# include <mlx.h>
# include <stdio.h>

int	parse(int argc, char **argv, t_data *data);

#endif /* MAIN_H */
