/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:24:00 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/18 16:30:23 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	set_wall_texture_path(char *img_path, t_map_id *id, t_images *imgs, int row)
{
	if (!img_path || !id || !imgs)
	{
		log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM);
		return (false);
	}
	if (ft_strncmp(id->id, "NO", id->id_len) == 0)
		imgs->north_wall = img_path;
	else if (ft_strncmp(id->id, "EA", id->id_len) == 0)
		imgs->east_wall = img_path;
	else if (ft_strncmp(id->id, "SO", id->id_len) == 0)
		imgs->south_wall = img_path;
	else if (ft_strncmp(id->id, "WE", id->id_len) == 0)
		imgs->west_wall = img_path;
	else
	{
		log_line_error(row, "unknown image type", __FILE__, __LINE__);
		return (false);
	}
	log_found_img(img_path, __FILE__, __LINE__);
	return (true);
}

/**
 * @brief Extracts image path from configuration line after identifier
 *
 * @param line The configuration line containing the image path
 * @param data_id Map identifier metadata
 * @param row Line number for error reporting
 * @return char* Allocated image path string, or NULL on error
 */
static size_t	extract_image_path(char **save, char *line, int row)
{
	size_t	skipped;

	if (!save || !line)
		return (log_msg(WARNING, __FILE__, __LINE__, LOG_INVALID_PARAM), 0);
	skipped = get_next_char_block(save, line);
	if (!*save || skipped == 0)
	{
		log_line_error(row, "no image path given", __FILE__, __LINE__);
		return (0);
	}
	return (skipped);
}

/**
 * @brief Extracts and validates XPM image path from configuration line
 *
 * Parses the line after the identifier to extract the image path,
 * validates that no extra content follows, and checks file extension.
 *
 * @param line The configuration line containing the image path
 * @param row Line number for error reporting
 * @param data_id Map identifier metadata
 * @return char* Allocated image path string, or NULL on error
 * @note Caller is responsible for freeing the returned string
 */
static char	*get_xmp_img_path(char *line, int row, t_map_id *data_id)
{
	char	*img_path;
	size_t	skipped;

	if (!line || !data_id)
		return (log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM), NULL);
	skipped = extract_image_path(&img_path, line, row);
	if (skipped == 0 || !img_path)
		return (NULL);
	if (has_trailing_content(line + skipped, row))
	{
		free(img_path);
		return (NULL);
	}
	if (correct_file_extension(img_path, ".xpm"))
	{
		free(img_path);
		return (NULL);
	}
	return (img_path);
}

/**
 * @brief Saves extracted image path to appropriate data structure field
 *
 * @param line The configuration line
 * @param row Line number for error reporting
 * @param data_id Map identifier metadata
 * @param data Main data structure to store image path
 * @return 0 on success, other on error
 */
int	save_image(char *line, int row, t_map_id *data_id, t_data *data)
{
	char	*img_path;

	if (!line || !data_id || !data)
	{
		log_msg(ERROR, __FILE__, __LINE__, LOG_INVALID_PARAM);
		return (1);
	}
	log_id_processing(data_id, __FILE__, __LINE__);
	img_path = line + data_id->id_len;
	img_path = get_xmp_img_path(img_path, row, data_id);
	if (!img_path)
		return (1);
	if (!set_wall_texture_path(img_path, data_id, &data->map_data.images, row))
	{
		free(img_path);
		return (1);
	}
	return (0);
}
