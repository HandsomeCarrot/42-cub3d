/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:03:08 by vpoka             #+#    #+#             */
/*   Updated: 2024/09/25 19:10:26 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

/* #include <stdio.h>
#include <bsd/string.h>
int main(void)
{
	char *str = "Hello NO what UP !?!?";
	char *search = "Hello NO what UP !?!?";
	int s = 21;
	printf("%s\n%s\n", strnstr(str, search, s), ft_strnstr(str, search, s));
} */