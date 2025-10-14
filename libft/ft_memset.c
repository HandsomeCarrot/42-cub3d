/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:42:56 by vpoka             #+#    #+#             */
/*   Updated: 2024/09/25 19:13:21 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Fills a block of memory with a specified value.
 *
 * The ft_memset() function fills the first n bytes of the memory area pointed
 *  to by s with the constant byte c.
 *
 * @param s Pointer to the memory area to be filled.
 * @param c Value to be set. The value is passed as an int, but the function
 *  fills the block of memory using the unsigned char conversion of this value.
 * @param n Number of bytes to be filled.
 *
 * @return A pointer to the memory area s.
 */
void	*ft_memset(void *s, int c, size_t n)
{
	char	*pos;

	pos = s;
	while (n > 0)
	{
		*pos = c;
		pos++;
		n--;
	}
	return (s);
}

/* #include <stdio.h>
int main(void)
{
	void *str = malloc(10 * sizeof(char));
	printf("%s\n", (char *)ft_memset(str, 'a', 5));
} */