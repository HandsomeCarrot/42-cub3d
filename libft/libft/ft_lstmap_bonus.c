/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:15:43 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/21 16:36:29 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Applies a function to each element of a linked list and creates a
 * new list.
 *
 * This function iterates through the linked list `lst`, applies the function `f`
 * to the content of each node, and creates a new linked list with the results.
 * If memory allocation fails at any point or if `f` returns NULL, the function
 * deletes the partially created new list using the `del` function to free the
 * allocated memory.
 *
 * @param lst The original linked list to map over.
 * Can be NULL, in which case NULL is returned.
 * 
 * @param f A function pointer that takes a void pointer
 * (the content of a list node) and returns a void pointer
 * (the new content for the new list). This function is applied to each
 * element's content.
 * 
 * @param del A function pointer used to delete the content of nodes if an
 * error occurs. It takes a void pointer and frees the associated memory.
 * 
 * @return A new linked list where each node's content is the result of applying
 * `f` to the corresponding node's content in the original list.
 * Returns NULL if `lst` is NULL, if memory allocation fails,
 * or if `f` returns NULL for any element.
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*new;

	if (!lst || !f || !del)
		return (NULL);
	res = NULL;
	while (lst)
	{
		new = ft_lstnew(f(lst->content));
		if (!new)
		{
			ft_lstclear(&res, del);
			return (NULL);
		}
		if (!res)
			res = new;
		else
			ft_lstadd_back(&res, new);
		lst = lst->next;
	}
	return (res);
}
