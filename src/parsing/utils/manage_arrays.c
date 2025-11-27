/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_arrays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 10:56:02 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/23 18:51:59 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/parsing.h"

/**
 * @brief Initializes a new dynamic array.
 *
 * @param member_size Size of each element in bytes.
 * @param capacity Initial capacity of the array.
 * @param array Pointer to the array structure to initialize.
 * @return 0 on success, 1 on error.
 */
int	new_array(size_t member_size, size_t capacity, t_array *array)
{
	if (member_size == 0 || capacity == 0 || !array)
		return (log_msg(WARNING, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	log_msg(DEBUG, __FILE__, __LINE__, "creating new array");
	array->ptr = log_calloc(member_size, capacity, __FILE__, __LINE__);
	if (!array->ptr)
		return (1);
	array->capacity = capacity;
	array->used_space = 0;
	array->member_size = member_size;
	return (0);
}

/**
 * @brief Expands the capacity of the dynamic array.
 *
 * Increases capacity by 1 and reallocates memory.
 *
 * @param array Pointer to the array structure.
 * @return 0 on success, 1 on error.
 */
int	expand_array(t_array *array)
{
	void	*new_ptr;

	if (!array)
		return (log_msg(WARNING, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	log_msg(DEBUG, __FILE__, __LINE__, "expanding array");
	new_ptr = log_calloc(array->capacity + 1, array->member_size,
			__FILE__, __LINE__);
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

/**
 * @brief Appends an element to the dynamic array.
 *
 * Expands the array if necessary.
 *
 * @param src Pointer to the element to append.
 * @param array Pointer to the array structure.
 * @return 0 on success, 1 on error.
 */
int	append_to_array(void *src, t_array *array)
{
	void	*dst;

	if (!src || !array)
		return (log_msg(WARNING, __FILE__, __LINE__, LOG_INVALID_PARAM), 1);
	log_msg(DEBUG, __FILE__, __LINE__, "appending to array");
	if (array->used_space >= array->capacity - 1 && expand_array(array))
		return (1);
	dst = array->ptr + (array->member_size * array->used_space);
	ft_memcpy(dst, src, array->member_size);
	array->used_space++;
	return (0);
}
