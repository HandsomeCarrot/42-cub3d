/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:51:40 by vpoka             #+#    #+#             */
/*   Updated: 2024/09/25 19:10:45 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Calculates the length of a null-terminated string.
 *
 * @param s The string to calculate the length of.
 * @return The length of the string.
 */
size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*(s + len))
		len++;
	return (len);
}
/* #include <stdio.h>
int main(void)
{
	char *s = "Hello";
	printf("%zu\n", ft_strlen(s));
} */