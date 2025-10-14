/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:13:47 by vpoka             #+#    #+#             */
/*   Updated: 2024/10/02 16:19:35 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

/*#include <stdio.h>
int	main(void)
{
	int i = 5;
	int j = 21;
	t_list *a = ft_lstnew(&j);
	t_list *b = ft_lstnew(&i);
	ft_lstadd_front(&a, b);
	t_list *c = ft_lstnew(&i);
	ft_lstadd_front(&b, c);
	t_list *d = ft_lstnew(&i);
	ft_lstadd_front(&c, d);
	t_list *e = ft_lstnew(&i);
	ft_lstadd_front(&d, e);
	t_list *o = ft_lstnew(&i);
	int res = *(int *)ft_lstlast(e)->content;
	int res2 = *(int *)ft_lstlast(o)->content;
	printf("%d | %d \n", res, res2);
}*/
