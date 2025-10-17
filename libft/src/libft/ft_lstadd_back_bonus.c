/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:25:48 by vpoka             #+#    #+#             */
/*   Updated: 2024/10/02 16:16:45 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @file ft_lstadd_back_bonus.c
 * @brief Adds a new element at the end of a linked list.
 *
 * This function takes a pointer to the first element of a linked list and a new
 * element to be added. It traverses the list to find the last element and adds
 * the new element at the end.
 *
 * @param lst A pointer to the first element of the list.
 * @param new The new element to be added to the list.
 */
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	last = ft_lstlast(*lst);
	if (!last)
		*lst = new;
	else
		last->next = new;
}

/*#include <stdio.h>
int	main(void)
{
	int i = 21;
	int j = 42;
	t_list *head = ft_lstnew(&i);
	t_list *new = ft_lstnew(&j);
	ft_lstadd_back(&head, new);
	int headi = *(int *)(head->content);
	int nexti = *(int *)head->next->content;
	printf("first: %d second: %d \n", headi, nexti);
}*/
