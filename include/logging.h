/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 19:34:28 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/27 15:29:47 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGING_H
# define LOGGING_H

# include "definitions.h"
# include "../libft/libft.h"
# include <stdio.h>

// 0 = ERROR
// 1 = WARNING
// 2 = INFO
// 3 = DEBUG
# ifndef LOGGING_LEVEL
#  define LOGGING_LEVEL 2
# endif /* LOGGING_LEVEL */

//-----COLOR-CODES-----//

# define NC "\033[0m"
# define GREEN "\033[1;42;37m"
# define YELLOW "\033[1;43;37m"
# define BLUE "\033[1;44;37m"
# define MAGENTA "\033[1;45;37m"
# define CYAN "\033[1;36m"
# define RED "\033[1;41;37m"

//-----GENERIC-MESSAGES-----//

# define LOG_INVALID_PARAM "got invalid parameter"
# define LOG_ALLOC_FAIL "memory allocation failed"

//-----logger.c-----//

int		log_start(t_log_level lvl, const char *file, int line);
void	log_msg(t_log_level lvl, const char *file, int line, char *msg);

//-----memory_logger.c-----//

void	*log_calloc(size_t nmemb, size_t size, const char *file, int line);
char	*log_get_next_line(int file_fd, char *src_file, int src_line);

#endif /* LOGGING_H */
