/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:36:56 by vpoka             #+#    #+#             */
/*   Updated: 2024/09/25 19:16:23 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Sets the first 'n' bytes of the memory pointed to by 's' to zero.
 *
 * @param s - Pointer to the memory to be zeroed.
 * @param n - Number of bytes to be zeroed.
 */
void	ft_bzero(void *s, size_t n)
{
	size_t	pos;

	pos = 0;
	while (pos < n)
	{
		*((char *)s + pos) = 0;
		pos++;
	}
}
