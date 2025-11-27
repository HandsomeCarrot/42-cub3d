/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:41:58 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/28 00:09:07 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "std_libft.h"

/**
 * Joins two strings together.
 *
 * @param s1 The first string to be joined.
 * @param s2 The second string to be joined.
 * @return The newly allocated string containing the joined strings,
 *         or NULL if the allocation fails.
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	s1_len;
	size_t	new_len;
	size_t	pos;

	s1_len = ft_strlen(s1);
	new_len = s1_len + ft_strlen(s2);
	if (new_len == 0)
		return (ft_strdup(""));
	res = malloc(new_len + 1);
	if (!res)
		return (NULL);
	pos = 0;
	while (s1[pos])
	{
		res[pos] = s1[pos];
		pos++;
	}
	while (*s2)
		res[pos++] = *s2++;
	res[pos] = '\0';
	return (res);
}
