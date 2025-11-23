/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:09:20 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/23 18:02:54 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "std_libft.h"

/**
 * @brief Creates a new list element.
 *
 * This function allocates (with malloc(3)) and returns a new element.
 * The variable 'content' is initialized with the value of the parameter
 *  'content'.
 * The variable 'next' is initialized to NULL.
 *
 * @param content The content to create the new element with.
 * @return t_list* The new element.
 */
t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}
