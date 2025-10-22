/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:17:00 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/22 16:06:59 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	count_strings(char **string_array)
{
	int	count;
	int	log_fd;

	count = 0;
	while (string_array + count)
		count++;
	log_fd = log_start(DEBUG, __FILE__, __LINE__);
	if (log_fd >= 0)
	{
		ft_putstr_fd("count ", log_fd);
		ft_putnbr_fd(count, log_fd);
		ft_putendl_fd(" strings in string array", log_fd);
	}
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
