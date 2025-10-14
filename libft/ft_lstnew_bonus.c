/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:09:20 by vpoka             #+#    #+#             */
/*   Updated: 2024/10/02 16:22:55 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
