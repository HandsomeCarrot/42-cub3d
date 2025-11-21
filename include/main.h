/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:26:06 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/21 23:47:09 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "definitions.h"

t_data	*init_data(void);
int		parse(int argc, char **argv, t_data *data);
void	main_cleanup(t_data *data);
void	log_msg(t_log_level lvl, const char *file, int line, char *msg);

#endif /* MAIN_H */
