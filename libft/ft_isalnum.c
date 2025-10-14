/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 14:02:39 by vpoka             #+#    #+#             */
/*   Updated: 2024/09/25 19:16:09 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if the given character is alphanumeric.
 *
 * @param c The character to be checked.
 * @return 1 if the character is alphanumeric, 0 otherwise.
 */
int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

/* #include <stdio.h>
int main(void)
{
	int i = 'a';
	printf("%d\n", ft_isalnum(i));
} */