/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 18:39:49 by vpoka             #+#    #+#             */
/*   Updated: 2024/09/30 19:10:38 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @file ft_striteri.c
 * @brief Applies a function to each character of a string, passing its index.
 *
 * This function iterates over each character of the string 's' and applies
 * the function 'f' to each character. The function 'f' is passed the index
 * of the character and a pointer to the character itself.
 *
 * @param s The string to iterate over.
 * @param f The function to apply to each character of the string.
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	pos;

	pos = 0;
	while (s[pos])
	{
		f(pos, (s + pos));
		pos++;
	}
}

/*void	pluspos(unsigned int n, char *s)
{
	*s = '0' + n;
}

#include <stdio.h>

int	main(void)
{
	char str[] = "9876543210";
	printf("%s\n", str);
	ft_striteri(str, &pluspos);
	printf("%s\n", str);
}*/
