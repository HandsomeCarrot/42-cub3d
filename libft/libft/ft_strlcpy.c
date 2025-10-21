/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:42:11 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/21 16:35:16 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Copies a string from source to destination with a specified size limit.
 *
 * @param dst The destination string where the copied string will be stored.
 * @param src The source string to be copied.
 * @param size The maximum number of characters to be copied, including the
 *  null-terminating character.
 * @return The total length of the string that was attempted to be copied.
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	pos;
	size_t	len;

	len = ft_strlen(src);
	if (size == 0)
		return (len);
	pos = 0;
	while (pos < size - 1 && *(src + pos))
	{
		*(dst + pos) = *(src + pos);
		pos++;
	}
	if (size > 0)
		*(dst + pos) = '\0';
	return (len);
}
