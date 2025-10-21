/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:42:26 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/21 16:36:06 by vpoka            ###   ########.fr       */
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
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	pos;

	pos = 0;
	if (!dest && !src)
		return (NULL);
	while (pos < n)
	{
		*((unsigned char *)dest + pos) = *((unsigned char *)src + pos);
		pos++;
	}
	return (dest);
}
