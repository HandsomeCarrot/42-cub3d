/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:13:47 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/28 00:09:07 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "std_libft.h"

/**
 * @brief Returns the last element of the list.
 *
 * This function traverses the linked list starting from the given node
 * and returns the last node in the list.
 *
 * @param lst The beginning of the list.
 * @return The last element of the list, or NULL if the list is empty.
 */
t_list	*ft_lstlast(t_list *lst)
{
	int	size;

	if (!lst)
		return (NULL);
	size = ft_lstsize(lst);
	while (size > 1)
	{
		lst = lst->next;
		size--;
	}
	return (lst);
}
