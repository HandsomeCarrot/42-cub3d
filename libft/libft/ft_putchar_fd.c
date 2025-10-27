/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 19:25:07 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/28 00:09:07 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "std_libft.h"

/**
 * @file ft_putchar_fd.c
 * @brief Outputs the character 'c' to the given file descriptor.
 *
 * This function writes the character 'c' to the file descriptor specified by
 *  'fd'.
 *
 * @param c The character to output.
 * @param fd The file descriptor on which to write.
 */
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, sizeof(char));
}
