/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:20:59 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/28 00:09:07 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "std_libft.h"

/**
 * @brief Creates a new string by extracting a substring from the given string.
 *
 * @param s The string from which to extract the substring.
 * @param start The starting index of the substring in the string.
 * @param len The length of the substring.
 *
 * @return The newly allocated substring, or NULL if the allocation fails.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*res;
	size_t			pos;
	unsigned int	s_len;
	int				r_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_calloc(1, sizeof(char)));
	r_len = len;
	if (len > s_len - start)
		r_len = s_len - start;
	res = malloc(r_len * sizeof(char) + 1);
	if (!res)
		return (NULL);
	pos = 0;
	while (pos < len && s[start + pos])
	{
		res[pos] = s[start + pos];
		pos++;
	}
	res[pos] = '\0';
	return (res);
}
