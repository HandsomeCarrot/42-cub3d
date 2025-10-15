/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:34:28 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/15 20:48:13 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGING_H
# define LOGGING_H

# include "libft.h"
# include <stdio.h>

# ifndef LOGGING_LEVEL
#  define LOGGING_LEVEL 1
# endif

# define LOG(level, msg) log_msg(level, __FILE__, __LINE__, msg)

typedef enum e_log_level
{
	NONE,
	ERROR,
	WARNING,
	INFO,
	DEBUG
}	t_log_level;

void	log_msg(t_log_level lvl, char *file, int line, char *msg);

#endif
