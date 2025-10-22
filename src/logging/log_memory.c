/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_memory.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 19:29:44 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/22 12:49:12 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logging.h"

void	*log_calloc(size_t nmemb, size_t size, char *file, int line)
{
	void	*ptr;

	ptr = ft_calloc(nmemb, size);
	if (!ptr)
		log_msg(ERROR, file, line, "memory allocation failed!");
	return (ptr);
}
