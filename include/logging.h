/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:34:28 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/21 19:23:05 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGING_H
# define LOGGING_H

# include "libft.h"
# include <stdio.h>

# ifndef LOGGING_LEVEL
#  define LOGGING_LEVEL 3
# endif /* LOGGING_LEVEL */

typedef enum e_log_level
{
	ERROR,
	WARNING,
	INFO,
	DEBUG
}	t_log_level;

void	log_msg(t_log_level lvl, char *file, int line, char *msg);

#endif /* LOGGING_H */
