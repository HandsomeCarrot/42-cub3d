/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:48:21 by vpoka             #+#    #+#             */
/*   Updated: 2024/09/25 19:07:19 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Converts a lowercase letter to its corresponding uppercase letter.
 *
 * @param c The character to be converted.
 * @return The uppercase equivalent of the given character, if it is a
 *  lowercase letter. Otherwise, the given character is returned unchanged.
 */
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
