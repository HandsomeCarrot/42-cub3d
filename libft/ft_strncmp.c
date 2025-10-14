/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:11:35 by vpoka             #+#    #+#             */
/*   Updated: 2024/09/23 17:10:49 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @file ft_strncmp.c
 * @brief Compares up to n characters of the null-terminated strings s1 and s2.
 *
 * This function compares the two strings s1 and s2. It returns an integer 
 * less than, equal to, or greater than zero if s1 is found, respectively, to 
 * be less than, to match, or be greater than s2. The comparison is done using 
 * unsigned characters, so that `\200' is greater than `\0'.
 *
 * @param s1 The first string to be compared.
 * @param s2 The second string to be compared.
 * @param n The maximum number of characters to compare.
 * @return An integer less than, equal to, or greater than zero if s1 
 * (or the first n characters thereof) is found, respectively, to be 
 * less than, to match, or be greater than s2.
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			pos;
	unsigned char	*u_s1;
	unsigned char	*u_s2;

	pos = 0;
	u_s1 = (unsigned char *)s1;
	u_s2 = (unsigned char *)s2;
	while (pos < n && (*(u_s1 + pos) || *(u_s2 + pos)))
	{
		if (*(u_s1 + pos) != *(u_s2 + pos))
			return (*(u_s1 + pos) - *(u_s2 + pos));
		pos++;
	}
	return (0);
}

/* #include <stdio.h>
int	main(void)
{
	char str[] = "test";
	char str2[] = "testss";
	printf("%d", ft_strncmp(str, str2, 5));
} */