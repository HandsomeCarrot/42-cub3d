/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:14:42 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/23 13:15:52 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cleanup.h"

/**
 * @brief Frees an array of strings and sets pointers to NULL.
 *
 * This function iterates through the array of strings, freeing each
 * individual string, and then frees the array itself. It sets all
 * pointers to NULL to prevent dangling pointers.
 *
 * @param string_array A triple pointer to the array of strings to be
 *                     freed. If NULL or the array is NULL, the function
 *                     returns early without error.
 *
 * @note This function is designed to handle NULL inputs gracefully and
 *       logs debug information during the freeing process.
 */
void	free_string_array(char ***string_array)
{
	int	pos;

	log_msg(DEBUG, __FILE__, __LINE__, "freeing string array");
	if (!string_array || !*string_array)
	{
		log_msg(WARNING, __FILE__, __LINE__, INVALID_PARAMETER);
		return ;
	}
	pos = 0;
	while (*string_array[pos])
	{
		free(*string_array[pos]);
		*string_array[pos] = NULL;
		pos++;
	}
	free(*string_array);
	*string_array = NULL;
}
