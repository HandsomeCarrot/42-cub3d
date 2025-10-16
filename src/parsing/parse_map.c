/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:39:39 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/16 19:32:45 by vpoka            ###   ########.fr       */
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
//static int	file_readable(char *file)
//{
//	(void)file;
//	return (0);
//}

/**
 * @brief Checks if the given file has the correct extension.
 *
 * This function verifies whether the file extension of the provided filename
 * matches the specified extension. It is used to validate file types during
 * parsing operations.
 *
 * @param file A null-terminated string representing the filename to check.
 * @param extension A null-terminated string representing the expected file extension
 *                  (e.g., ".cub" for Cub3D map files).
 * @return 0 if the file extension matches, 1 on any error.
 */
static int	correct_file_extension(char *file, char *extension)
{
	size_t	file_name_len;
	size_t	extension_len;
	size_t	file_extension;

	if (!file || !extension)
	{
		log_msg(ERROR, __FILE__, __LINE__, "got NULL pointer");
		return (1);
	}
	file_name_len = ft_strlen(file);
	extension_len = ft_strlen(extension);
	file_extension = file_name_len - extension_len;
	if (file_name_len <= extension_len
		|| file[0] == '.'
		|| ft_strncmp((file + file_extension), extension, extension_len) != 0)
	{
		log_msg(ERROR, __FILE__, __LINE__, "invalid file name '");
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putendl_fd("'", STDERR_FILENO);
		return (1);
	}
	return (0);
}
