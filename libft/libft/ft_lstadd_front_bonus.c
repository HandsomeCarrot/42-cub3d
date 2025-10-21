/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:54:52 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/21 16:36:54 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @file ft_lstadd_front_bonus.c
 * @brief Adds a new element at the beginning of the list.
 *
 * This function takes a pointer to the first element of a list and a new
 *  element,
 * and inserts the new element at the beginning of the list.
 *
 * @param lst A pointer to the first element of the list.
 * @param new The new element to be added to the list.
 */
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}
