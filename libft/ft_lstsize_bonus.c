/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:39:05 by vpoka             #+#    #+#             */
/*   Updated: 2024/10/02 16:23:37 by vpoka            ###   ########.fr       */
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

/*#include <stdio.h>
int	main(void)
{
	int i = 5;
	t_list *a = ft_lstnew(&i);
	t_list *b = ft_lstnew(&i);
	ft_lstadd_front(&a, b);
	t_list *c = ft_lstnew(&i);
	ft_lstadd_front(&b, c);
	t_list *d = ft_lstnew(&i);
	ft_lstadd_front(&c, d);
	t_list *e = ft_lstnew(&i);
	ft_lstadd_front(&d, e);
	t_list *n = NULL;
	t_list *o = ft_lstnew(&i);
	printf("%d", ft_lstsize(o));
}*/