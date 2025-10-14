/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:05:05 by vpoka             #+#    #+#             */
/*   Updated: 2024/10/02 10:20:27 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Checks if a character is present in a given set of characters.
 *
 * @param c   The character to check.
 * @param set The set of characters to check against.
 * @return    1 if the character is present in the set, 0 otherwise.
 */
static int	in_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

/**
 * @brief Calculates the length of a substring in a given string, excluding
 * characters specified in the set.
 *
 * This function calculates the length of a substring in the string `s1`,
 * starting from the index `start`,
 * and excluding any characters that are present in the string `set`.
 *
 * @param s1 The string to search for the substring.
 * @param set The characters to exclude from the substring.
 * @param start The starting index of the substring.
 * @return The length of the substring.
 */
static int	getlen(char const *s1, char const *set, int start)
{
	int	end;
	int	len;

	end = 0;
	len = ft_strlen(s1);
	while (len > start && in_set(s1[(len - 1) - end], set) == 1)
		end++;
	return ((len - end) - start);
}

/**
 * @brief Trims the specified characters from the beginning and end of a string.
 *

	* This function takes a string `s1` and a set of characters `set` and 
	returns a new string
 * with all leading and trailing characters from `set` removed.
 *
 * @param s1 The string to be trimmed.
 * @param set The set of characters to be removed.
 * @return The trimmed string, or NULL if memory allocation fails.
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		res_len;
	int		start;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	start = 0;
	while (s1[start] && in_set(s1[start], set) == 1)
		start++;
	res_len = getlen(s1, set, start);
	if (res_len <= 0)
		return (ft_calloc(1, sizeof(char)));
	res = ft_substr(s1, start, res_len);
	if (!res)
		return (NULL);
	return (res);
}

/*#include <stdio.h>
int	main(void)
{
	char *str = "abcHallöliabc";
	char *set = "abc";
	printf("%s\n", ft_strtrim(str, set));
}*/
