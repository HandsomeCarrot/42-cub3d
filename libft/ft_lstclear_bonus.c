/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:09:19 by vpoka             #+#    #+#             */
/*   Updated: 2024/10/02 16:17:30 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @file ft_lstclear_bonus.c
 * @brief Clears and frees the memory of a linked list.
 *
 * This function deletes and frees the given linked list and its elements
 * using the function 'del' and free(3). The pointer to the list is set to NULL.
 *
 * @param lst A pointer to the pointer of the first element of the list.
 * @param del A pointer to the function used to delete the content of an element.
 */
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;

	while (*lst)
	{
		next = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = next;
	}
	*lst = NULL;
}
