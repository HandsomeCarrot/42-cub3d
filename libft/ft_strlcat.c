/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:21:33 by vpoka             #+#    #+#             */
/*   Updated: 2024/09/25 19:12:17 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Concatenates the string pointed to by `src` to the end of the string
 *        pointed to by `dst` (overwriting the null character at the end of
 *  `dst`)
 *        and ensures that the resulting string is null-terminated.
 * 
 * @param dst   Pointer to the destination string.
 * @param src   Pointer to the source string.
 * @param size  Size of the destination buffer.
 * 
 * @return The total length of the string that would have been created if there
 *         was enough space, excluding the null-terminating character.
 */
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	pos;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size <= dst_len)
		return (size + src_len);
	pos = 0;
	while (src[pos] && (dst_len + pos) < (size - 1))
	{
		dst[dst_len + pos] = src[pos];
		pos++;
	}
	dst[dst_len + pos] = '\0';
	return (dst_len + src_len);
}

/* #include <stdio.h>
int	main(void)
{
	char	src[] = "Yo Bro.";
	char	dst[20] = "NO!";

	printf("%ld\n%s\n", ft_strlcat(dst, src, 5), dst);
} */
