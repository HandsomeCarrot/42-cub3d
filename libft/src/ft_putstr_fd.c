/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:35:07 by vpoka             #+#    #+#             */
/*   Updated: 2024/10/01 14:47:02 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @file ft_putstr_fd.c
 * @brief Outputs a string to the given file descriptor.
 *
 * This function takes a string and a file descriptor as arguments and writes
 * the string to the specified file descriptor.
 *
 * @param s The string to be written.
 * @param fd The file descriptor on which to write.
 */
void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
	{
		ft_putchar_fd(*s, fd);
		s++;
	}
}

/*#include <fcntl.h>
int main(void)
{
	ft_putstr_fd("Hello World.\nHow are you!", 2);
}*/
