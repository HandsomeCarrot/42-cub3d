/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:00:50 by vpoka             #+#    #+#             */
/*   Updated: 2024/09/30 19:14:15 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @file ft_strmapi.c
 * @brief Applies a function to each character of a string to create a new
 *  string.
 *
 * This function iterates over each character of the input string `s`, applies
 *  the
 * function `f` to each character along with its index, and constructs a new
 *  string
 * from the results of these function applications.
 *
 * @param s The input string on which to apply the function.
 * @param f The function to apply to each character of the string. It takes an
 *          unsigned int (the index of the character) and a char
 *  (the character itself),
 *          and returns a char (the transformed character).
 * @return A new string resulting from applying the function `f`
 *  to each character of `s`.
 *         Returns NULL if memory allocation fails.
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*res;
	int		pos;

	res = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	pos = 0;
	while (s[pos])
	{
		res[pos] = f(pos, s[pos]);
		pos++;
	}
	res[pos] = '\0';
	return (res);
}

/*char	toupper2(unsigned int n, char c)
{
	return (c + n);
}

#include <stdio.h>
int main(void)
{
	printf("%s\n", ft_strmapi("9876543210", &toupper2));
}*/
