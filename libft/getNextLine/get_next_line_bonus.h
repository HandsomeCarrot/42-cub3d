/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:23:00 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/21 02:13:34 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif /* BUFFER_SIZE */

# ifndef MAX_FD
#  define MAX_FD 10
# endif /* MAX_FD */

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
size_t	gnl_strlen(const char *s);
char	*gnl_strdup(const char *s);
char	*gnl_strjoin(char const *s1, char const *s2);
char	*gnl_strchr(const char *s, int c);
char	*gnl_substr(char const *s, unsigned int start, size_t len);

#endif /* GET_NEXT_LINE_BONUS_H */