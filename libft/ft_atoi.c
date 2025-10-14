/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:13:03 by vpoka             #+#    #+#             */
/*   Updated: 2024/09/25 19:16:37 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Converts a string to an integer.
 *
 * This function takes a string `nptr` and converts it to an integer.
 *
 * @param nptr The string to be converted.
 * @return The converted integer value.
 */
int	ft_atoi(const char *nptr)
{
	long	res;
	int		sign;

	sign = 1;
	res = 0;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\n' || *nptr == '\v'
		|| *nptr == '\f' || *nptr == '\r')
		nptr++;
	if (*nptr == '-')
		sign = -1;
	if (*nptr == '+' || *nptr == '-')
		nptr++;
	while (ft_isdigit(*nptr))
	{
		res = res * 10 + (*nptr - '0');
		if (res > INT_MAX)
		{
			if (sign == 1)
				return (INT_MAX);
			else
				return (INT_MIN);
		}
		nptr++;
	}
	return (sign * res);
}

/* #include <stdio.h>
int	main(void)
{
	char *n = "   -2147483648";
	printf("%d\n", ft_atoi(n));
} */
