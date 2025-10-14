/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:56:34 by vpoka             #+#    #+#             */
/*   Updated: 2024/09/24 12:44:20 by vpoka            ###   ########.fr       */
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

/*#include <stdio.h>
int	main(void)
{
	char *str = "Hello";
	char *cpy = ft_strdup(str);
	printf("%s\n", cpy);
}*/