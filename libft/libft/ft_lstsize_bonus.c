/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:39:05 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/21 16:36:16 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @file ft_lstsize_bonus.c
 * @brief Implementation of a function to count the number of elements in a
 *  linked list.
 *
 * This file contains the implementation of the ft_lstsize function, which
 * traverses a linked list and returns the number of elements it contains.
 *
 * @param lst A pointer to the first element of the linked list.
 * @return The number of elements in the linked list.
 */
int	ft_lstsize(t_list *lst)
{
	int	res;

	res = 0;
	while (lst)
	{
		res++;
		lst = lst->next;
	}
	return (res);
}
