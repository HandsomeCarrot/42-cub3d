/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:23:00 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/17 20:41:07 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
size_t	gnl_ft_strlen(const char *s);
char	*gnl_ft_strdup(const char *s);
char	*gnl_ft_strjoin(char const *s1, char const *s2);
char	*gnl_ft_strchr(const char *s, int c);
char	*gnl_ft_substr(char const *s, unsigned int start, size_t len);

#endif