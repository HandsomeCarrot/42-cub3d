/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 13:43:47 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/28 00:09:07 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "std_libft.h"

/**
 * @file ft_lstdelone_bonus.c
 * @brief Deletes a single element from a linked list.
 *
 * This function takes a pointer to a list element and a function pointer
 * to a delete function. It applies the delete function to the content of
 * the list element and then frees the memory allocated for the element.
 *
 * @param lst A pointer to the list element to delete.
 * @param del A function pointer to a function that deletes the content of
 *  the element.
 */
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
}
