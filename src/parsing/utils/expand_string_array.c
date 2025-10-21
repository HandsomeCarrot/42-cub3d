/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:17:00 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/21 19:36:36 by vpoka            ###   ########.fr       */
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
	return (count);
}

char	**expand_string_array(char **old_array)
{
	char	**new_array;
	int		strings;

	log_msg(DEBUG, __FILE__, __LINE__, "expanding string array\n");
	strings = count_strings(old_array);
	log_msg(DEBUG, __FILE__, __LINE__, "allocating new array\n");
	new_array = log_calloc(strings + 2, sizeof(char *), __FILE__, __LINE__);
	if (!new_array)
		return (NULL);
	//...
}
