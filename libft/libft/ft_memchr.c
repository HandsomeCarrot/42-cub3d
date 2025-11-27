/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:02:05 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/28 00:09:07 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "std_libft.h"

/**
 * Searches for the first occurrence of the character 'c'
 *  (converted to an unsigned char)
 * in the first 'n' bytes of the memory area pointed to by 's'.
 *
 * @param s - Pointer to the memory area to be searched.
 * @param c - Character to be located.
 * @param n - Number of bytes to be searched.
 * @return A pointer to the first occurrence of 'c' in the memory area pointed
 *  to by 's',
 *         or NULL if the character is not found within the first 'n' bytes.
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*u_s;
	unsigned char	u_c;

	u_s = (unsigned char *)s;
	u_c = c;
	while (n > 0)
	{
		if (*u_s == u_c)
			return (u_s);
		u_s++;
		n--;
	}
	return (NULL);
}
