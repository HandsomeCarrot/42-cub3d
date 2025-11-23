/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:54:52 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/23 18:00:27 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "std_libft.h"

/**
 * @file ft_lstadd_front_bonus.c
 * @brief Adds a new element at the beginning of the list.
 *
 * This function takes a pointer to the first element of a list and a new
 *  element,
 * and inserts the new element at the beginning of the list.
 *
 * @param lst A pointer to the first element of the list.
 * @param new_node The new element to be added to the list.
 */
void	ft_lstadd_front(t_list **lst, t_list *new_node)
{
	new_node->next = *lst;
	*lst = new_node;
}
