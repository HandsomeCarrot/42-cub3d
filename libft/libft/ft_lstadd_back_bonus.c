/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:25:48 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/23 18:05:07 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "std_libft.h"

/**
 * @file ft_lstadd_back_bonus.c
 * @brief Adds a new element at the end of a linked list.
 *
 * This function takes a pointer to the first element of a linked list and a new
 * element to be added. It traverses the list to find the last element and adds
 * the new element at the end.
 *
 * @param lst A pointer to the first element of the list.
 * @param new_node The new element to be added to the list.
 */
void	ft_lstadd_back(t_list **lst, t_list *new_node)
{
	t_list	*last;

	last = ft_lstlast(*lst);
	if (!last)
		*lst = new_node;
	else
		last->next = new_node;
}
