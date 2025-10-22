/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:34:28 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/22 12:51:54 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGING_H
# define LOGGING_H

# include "libft.h"
# include <stdio.h>

# ifndef LOGGING_LEVEL
#  define LOGGING_LEVEL 2
# endif /* LOGGING_LEVEL */

typedef enum e_log_level
{
	ERROR,
	WARNING,
	INFO,
	DEBUG
}		t_log_level;

//-----logging.c-----//

int		log_start(t_log_level lvl, char *file, int line);
void	log_msg(t_log_level lvl, char *file, int line, char *msg);

//-----log_memory.c-----//

void	*log_calloc(size_t nmemb, size_t size, char *file, int line);

#endif /* LOGGING_H */
