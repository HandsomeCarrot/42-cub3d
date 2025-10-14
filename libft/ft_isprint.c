/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:42:01 by vpoka             #+#    #+#             */
/*   Updated: 2024/09/25 19:15:20 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Checks if a character is a printable character.
 *
 * @param c The character to be checked.
 * @return 1 if the character is a printable character, 0 otherwise.
 */
int	ft_isprint(int c)
{
	if (c >= ' ' && c <= 126)
		return (1);
	return (0);
}
