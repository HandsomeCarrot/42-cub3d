/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:03:08 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/28 00:09:07 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "std_libft.h"

/**
 * @brief Locates the first occurrence of the null-terminated string `little`
 *        in the null-terminated string `big`, where not more than `len`
 *        characters are searched.
 *
 * @param big The null-terminated string to be searched.
 * @param little The null-terminated string to search for.
 * @param len The maximum number of characters to search.
 * 
 * @return If `little` is an empty string, `big` is returned; if `little`
 *  occurs
 *         nowhere in `big`, `NULL` is returned; otherwise, a pointer to the
 *         first character of the first occurrence of `little` is returned.
 */
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	bpos;
	size_t	lpos;

	if (!*little)
		return ((char *)big);
	bpos = 0;
	while (big[bpos] && bpos < len)
	{
		lpos = 0;
		while (big[bpos + lpos] == little[lpos] && big[bpos + lpos]
			&& little[lpos] && (bpos + lpos) < len)
			lpos++;
		if (little[lpos] == '\0')
			return ((char *)big + bpos);
		bpos++;
	}
	return (NULL);
}
