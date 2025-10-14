/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:54:52 by vpoka             #+#    #+#             */
/*   Updated: 2024/10/02 16:23:20 by vpoka            ###   ########.fr       */
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

/*#include <stdio.h>
int main(void)
{
	int i = 21;
	int j = 42;
	t_list *head = ft_lstnew(&i);
	t_list *new = ft_lstnew(&j);
	ft_lstadd_front(&head, new);
	int headi = *(int *)(head->content);
	int nexti = *(int *)head->next->content;
	printf("first: %d second: %d", headi, nexti);
}*/