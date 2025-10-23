/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:17:00 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/23 18:37:07 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Counts the number of strings in a null-terminated string array.
 *
 * This function iterates through the provided string array until it
 * encounters a NULL pointer, counting the number of valid strings.
 * It also logs the count for debugging purposes.
 *
 * @param string_array The array of strings to count. Must be
 *                     null-terminated.
 * @return The number of strings in the array.
 */
static int	count_strings(char **string_array)
{
	int	count;
	int	log_fd;

	count = 0;
	log_fd = log_start(DEBUG, __FILE__, __LINE__);
	if (log_fd >= 0)
		ft_putstr_fd("counting string array size: ", log_fd);
	while (string_array && string_array[count])
		count++;
	if (log_fd >= 0)
	{
		ft_putnbr_fd(count, log_fd);
		ft_putendl_fd(" strings", log_fd);
	}
	return (count);
}

/**
 * @brief Copies strings from one array to another up to a specified size.
 *
 * This function copies strings from the old array to the new array,
 * ensuring not to exceed the new array's size. It logs the operation
 * for debugging.
 *
 * @param new_array The destination array where strings will be copied.
 * @param old_array The source array from which strings are copied.
 * @param new_array_size The maximum number of strings to copy.
 */
static void	copy_array(char **new_array, char **old_array, int new_array_size)
{
	int	string;

	string = 0;
	log_msg(DEBUG, __FILE__, __LINE__, "moving strings array to another array");
	while (old_array[string] && string < new_array_size)
	{
		new_array[string] = old_array[string];
		string++;
	}
}

/**
 * @brief Expands the size of a string array by allocating a new array.
 *
 * This function creates a new array with space for one additional string
 * compared to the original array. It copies the existing strings and
 * frees the old array. Logs the expansion process.
 *
 * @param old_array Pointer to the old array, which will be modified
 *                  to point to the new array.
 * @return The new expanded array, or NULL if allocation fails or
 *         invalid parameters are provided.
 */
char	**expand_string_array(char ***old_array)
{
	char	**new_array;
	int		strings;

	log_msg(DEBUG, __FILE__, __LINE__, "expanding string array size");
	if (!old_array)
		return (log_msg(WARNING, __FILE__, __LINE__, INVALID_PARAMETER), NULL);
	strings = count_strings(*old_array);
	new_array = log_calloc(strings + 2, sizeof(char *), __FILE__, __LINE__);
	if (!new_array)
		return (free_string_array(old_array, __FILE__, __LINE__), NULL);
	if (*old_array)
	{
		copy_array(new_array, *old_array, strings);
		free(*old_array);
	}
	return (new_array);
}
