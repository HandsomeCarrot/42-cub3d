/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:03:52 by vpoka             #+#    #+#             */
/*   Updated: 2024/09/25 19:09:48 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Searches for the last occurrence of a character in a string.
 *
 * @param s The string to search in.
 * @param c The character to search for.
 * @return A pointer to the last occurrence of the character in the string,
 *         or NULL if the character is not found.
 */
char	*ft_strrchr(const char *s, int c)
{
	size_t	size;
	char	*end;

	size = ft_strlen(s);
	end = (char *)s + size;
	while (end >= s)
	{
		if (*end == (char)c)
			return (end);
		end--;
	}
	return (NULL);
}

/* #include <stdio.h>
int	main(void)
{
	char str[] = "Hello World!";
	printf("%s\n", ft_strrchr(str, 'o'));
} */