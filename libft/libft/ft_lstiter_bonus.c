/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:54:06 by vpoka             #+#    #+#             */
/*   Updated: 2024/10/02 16:20:57 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @file ft_lstiter_bonus.c
 * @brief Iterates over a list and applies a function to each element.
 *
 * This function takes a list and a function pointer as arguments. It iterates
 * over each element of the list and applies the given function to the content
 * of each element.
 *
 * @param lst A pointer to the first element of the list.
 * @param f A function pointer to a function that takes a void pointer as an
 * argument and returns nothing. This function will be applied to the content
 * of each element in the list.
 */
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
