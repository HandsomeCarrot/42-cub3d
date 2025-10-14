/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:24:25 by vpoka             #+#    #+#             */
/*   Updated: 2024/10/01 13:41:17 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @file ft_putnbr_fd.c
 * @brief Outputs the integer n to the given file descriptor.
 *
 * This function takes an integer n and a file descriptor fd, and writes
 * the integer to the file descriptor. It handles the conversion of the
 * integer to its string representation and ensures that the entire number
 * is written correctly, including handling negative numbers.
 *
 * @param n The integer to be written.
 * @param fd The file descriptor on which to write.
 */
void	ft_putnbr_fd(int n, int fd)
{
	if (n == INT_MIN)
	{
		ft_putstr_fd("-2147483648", fd);
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n, fd);
	}
	else if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
		ft_putchar_fd('0' + n, fd);
}

/*#include <fcntl.h>
int	main(void)
{
	ft_putnbr_fd(2142069, 2);
}*/
