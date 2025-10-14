/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:50:06 by vpoka             #+#    #+#             */
/*   Updated: 2024/09/25 19:13:44 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Copies a block of memory from a source address to a destination address.
 *
 * @param dest The pointer to the destination address where the memory will be
 *  copied to.
 * @param src The pointer to the source address where the memory will be copied
 *  from.
 * @param n The number of bytes to be copied.
 * @return A pointer to the destination address.
 */
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int	pos;

	if (!dest && !src)
		return (dest);
	if (dest < src)
	{
		pos = 0;
		while (pos < (int)n)
		{
			*(unsigned char *)(dest + pos) = *(unsigned char *)(src + pos);
			pos++;
		}
	}
	else
	{
		pos = (int)n - 1;
		while (pos >= 0)
		{
			*(unsigned char *)(dest + pos) = *(unsigned char *)(src + pos);
			pos--;
		}
	}
	return (dest);
}

/* #include <stdio.h>
#include <string.h>
int	main(void)
{
	char s[] = "Hello mate!";
	char *d = s + 6;
	printf("%s\n%s\n", s, d);
	printf("%s\n%s\n", (char *)memmove(d, s, 5), (char *)ft_memmove(d, s, 5));
} */