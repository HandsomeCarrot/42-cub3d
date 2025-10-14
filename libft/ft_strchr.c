/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:50:40 by vpoka             #+#    #+#             */
/*   Updated: 2024/10/01 17:12:27 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

/*#include <stdio.h>
int main(void)
{
	char *str = "AbcdeFghIjkLmnOpQrstuvwxYz";
	printf("%s\n", ft_strchr(str, 'F'));
}*/
