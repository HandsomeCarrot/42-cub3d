/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:16:46 by codespace         #+#    #+#             */
/*   Updated: 2024/09/25 19:14:42 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Compares the first n bytes of memory areas s1 and s2.
 *
 * @param s1 Pointer to the first memory area.
 * @param s2 Pointer to the second memory area.
 * @param n Number of bytes to compare.
 * @return An integer less than, equal to, or greater than zero if the first
 *  n bytes of s1 are found, respectively, to be less than, to match, or be
 *  greater than the first n bytes of s2.
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*u_s1;
	unsigned char	*u_s2;

	u_s1 = (unsigned char *)s1;
	u_s2 = (unsigned char *)s2;
	while (n > 0 && (u_s1 || u_s2))
	{
		if (*u_s1 != *u_s2)
			return (*u_s1 - *u_s2);
		u_s1++;
		u_s2++;
		n--;
	}
	return (0);
}

/* #include <stdio.h>
#include <string.h>

int	main(void)
{
	char str[] = "Halloli";
	char str2[] = "";
	printf("memcmp: %d\nft_memcmp: %d\n", memcmp(str, str2, 5), ft_memcmp(str,
			str2, 5));
} */