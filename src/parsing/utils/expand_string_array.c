/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:17:00 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/22 13:23:52 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	count_strings(char **string_array)
{
	int	count;

	count = 0;
	while (string_array + count)
		count++;
	log_msg(DEBUG, __FILE__, __LINE__, "counted ");
	ft_putnbr_fd(count, STDOUT_FILENO);
	ft_putendl_fd(" strings in string array", STDOUT_FILENO);
	// fix these messages to only print with the previously specified log level
	return (count);
}

static void	copy_array(char **new_array, char **old_array, int new_array_size)
{
	int	string;

	string = 0;
	while (old_array[string] && string < new_array_size)
	{
		new_array[string] = old_array[string];
		string++;
	}
}

char	**expand_string_array(char **old_array)
{
	char	**new_array;
	int		strings;

	log_msg(DEBUG, __FILE__, __LINE__, "expanding string array");
	strings = count_strings(old_array);
	new_array = log_calloc(strings + 2, sizeof(char *), __FILE__, __LINE__);
	if (!new_array)
		return (NULL);
	copy_array(new_array, old_array, strings);
	return (new_array);
}
