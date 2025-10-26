/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 13:14:42 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/26 11:45:08 by vpoka            ###   ########.fr       */
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
void	free_string_array(char ***string_array, char *src_file, int src_line)
{
	int	log_fd;
	int	pos;

	log_msg(DEBUG, src_file, src_line, "freeing string array");
	if (!string_array || !*string_array)
	{
		log_msg(WARNING, __FILE__, __LINE__, LOG_INVALID_PARAM);
		return ;
	}
	pos = 0;
	while ((*string_array)[pos])
	{
		log_fd = log_start(DEBUG, __FILE__, __LINE__);
		if (log_fd >= 0)
		{
			ft_putstr_fd("freeing string at position ", log_fd);
			ft_putnbr_fd(pos, log_fd);
			ft_putchar_fd('\n', log_fd);
		}
		free((*string_array)[pos]);
		(*string_array)[pos] = NULL;
		pos++;
	}
	free(*string_array);
	*string_array = NULL;
}
