/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:39:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/16 18:58:22 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief checks if the file exists and can be read.
 * 
 * @param file the given file
 * 
 * @return 1 on error, 0 on success.
 */
static int	file_readable(char *file)
{
	return (0);
}

/**
 * @brief checks if the file has 'extension' as extension.
 * 
 * Looks at the last characters of file and compares them to 'extension'.
 * If they are identical, then it returns 0. If there is a difference it
 * returns 1.
 * 
 * @param file the file path
 * @param extension the extension to compare it to (.cub, ...)
 * 
 * @return 1 on error, 0 on success.
 */
static int	correct_file_extension(char *file, char *extension)
{
	int	file_name_len;
	int	extension_len;
	int	file_extension;

	if (!file || !extension)
	{
		log_msg(ERROR, __FILE__, __LINE__, "got NULL pointer");
		return (1);
	}
	file_name_len = ft_strlen(file);
	extension_len = ft_strlen(extension);
	file_extension = file_name_len - extension_len;
	if (ft_strncmp((file + file_extension), extension, extension_len) != 0)
	{
		log_msg(ERROR, __FILE__, __LINE__, "invalid file extension");
		return (1);
	}
	return (0);
}
