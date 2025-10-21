/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:56:34 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/21 16:35:36 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Duplicates a string.
 *
 * This function allocates sufficient memory for a copy of the string s,
 * does the copy, and returns a pointer to it. The memory allocated for
 * the new string is obtained with malloc and can be freed with free.
 *
 * @param s The string to duplicate.
 * @return A pointer to the duplicated string, or NULL if insufficient memory
 *  was available.
 */
char	*ft_strdup(const char *s)
{
	char	*str;
	int		s_len;
	int		pos;

	s_len = ft_strlen(s);
	str = malloc(s_len * sizeof(char) + 1);
	if (!str)
		return (NULL);
	pos = 0;
	while (pos <= s_len)
	{
		str[pos] = s[pos];
		pos++;
	}
	return (str);
}
