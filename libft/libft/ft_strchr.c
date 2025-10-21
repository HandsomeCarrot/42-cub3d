/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:50:40 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/21 16:33:58 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Locates the first occurrence of a character in a string.
 *
 * This function searches for the first occurrence of the character `c`
 * (converted to a char) in the string `s`. The search includes the
 * terminating null character, allowing the function to locate the
 * null terminator itself.
 *
 * @param s A pointer to the null-terminated string to be searched.
 * @param c The character to search for, passed as an int but converted
 *          to char for comparison.
 * @return A pointer to the first occurrence of the character in the
 *         string, or NULL if the character is not found.
 * @note The character parameter `c` is converted to char before
 *       comparison, which may affect extended ASCII characters.
 * @warning This function searches for the null terminator if `c` is 0,
 *          returning a pointer to the end of the string.
 */
char	*ft_strchr(const char *s, int c)
{
	char	*res;

	res = (char *)s;
	while (*res)
	{
		if (*res == (char)c)
			return (res);
		res++;
	}
	if (*res == (char)c)
		return (res);
	return (NULL);
}
