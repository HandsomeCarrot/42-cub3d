/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 10:56:02 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/05 11:37:37 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @return 0 on success, 1 on error
 */
int	expand_array(t_array *array)
{
	void	*new_ptr;

	if (!array)
		return (log_msg(WARNING, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	log_msg(DEBUG, __FILE__, __LINE__, "expanding array");
	new_ptr = log_calloc(array->capacity + 1, array->member_size, __FILE__, __LINE__);
	if (!new_ptr)
		return (1);
	array->capacity++;
	if (array->ptr)
	{
		ft_memcpy(new_ptr, array->ptr, array->member_size * array->used_space);
		free(array->ptr);
	}
	array->ptr = new_ptr;
	return (0);
}

int	append_to_array(void *src, t_array *array)
{
	void	*dst;

	if (!src || !array)
		return (log_msg(WARNING, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	log_msg(DEBUG, __FILE__, __LINE__, "appending to array");
	if (array->used_space == array->capacity && expand_array(array))
		return (1);
	dst = array->ptr + (array->member_size * (array->used_space - 1));
	ft_memcpy(dst, src, array->member_size);
	array->used_space++;
	return (0);
}
