/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:26:06 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/27 15:29:26 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "definitions.h"
# include "../libft/libft.h"

int		parse(int argc, char **argv, t_map_data *map_data);
void	main_cleanup(t_map_data *data);
void	log_msg(t_log_level lvl, const char *file, int line, char *msg);

#endif /* MAIN_H */
