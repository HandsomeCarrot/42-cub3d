/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:11:41 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/21 16:35:49 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @file ft_putendl_fd.c
 * @brief Outputs the string 's' to the given file descriptor, followed by a
 *  newline.
 *
 * This function writes the string 's' to the file descriptor specified by 'fd',
 * followed by a newline character. It is useful for writing strings to files or
 * other output streams that are represented by file descriptors.
 *
 * @param s The string to output.
 * @param fd The file descriptor to write to.
 */
void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}
