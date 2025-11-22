/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_parsing_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 20:08:44 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/22 13:13:03 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logging.h"

/**
 * @brief Logs an error message for an invalid file name.
 *
 * This static function logs an error indicating that the provided map
 * file name is invalid, typically due to incorrect extension or format.
 * It uses the logging system to output the error message.
 *
 * @param file The name of the file that is invalid.
 * @param src_file The source file name where the error occurred.
 * @param line The line number in the source file where the error was
 *             detected.
 */
void	log_extension_error(const char *file, const char *message,
		const char *src_file, int line)
{
	int	log_fd;

	log_fd = log_start(ERROR, src_file, line);
	if (log_fd >= 0)
	{
		ft_putstr_fd("invalid file name '", log_fd);
		ft_putstr_fd((char *)file, log_fd);
		ft_putstr_fd("': ", log_fd);
		ft_putendl_fd((char *)message, log_fd);
	}
}

/**
 * @brief Logs a line-based error with customizable message.
 *
 * This function logs an error that includes a line number and a
 * customizable error message. Useful for various parsing errors.
 *
 * @param line_num The line number where the error occurred.
 * @param message The specific error message to display.
 * @param src_file The source file name where the error occurred.
 * @param line The line number in the source file.
 */
void	log_line_error(int line_num, const char *message, const char *src_file,
		int line)
{
	int	log_fd;

	log_fd = log_start(ERROR, src_file, line);
	if (log_fd >= 0)
	{
		ft_putstr_fd("in map on line ", log_fd);
		ft_putnbr_fd(line_num, log_fd);
		ft_putstr_fd(": ", log_fd);
		ft_putendl_fd((char *)message, log_fd);
	}
}

/**
 * @brief Logs the start of processing for a map identifier.
 *
 * @param data_id The map identifier being processed.
 * @param src_file The source file calling this function.
 * @param src_line The source line calling this function.
 */
void	log_id_processing(t_map_id *data_id, char *src_file, int src_line)
{
	int	log_fd;

	if (!data_id || !src_file)
	{
		log_msg(WARNING, __FILE__, __LINE__, LOG_INVALID_PARAM);
		return ;
	}
	log_fd = log_start(INFO, src_file, src_line);
	if (log_fd < 0)
		return ;
	ft_putstr_fd("extracting data for ", log_fd);
	if (data_id->type == T_IMAGE)
		ft_putstr_fd("image ", log_fd);
	else if (data_id->type == T_COLOR)
		ft_putstr_fd("color ", log_fd);
	if (data_id->id)
		ft_putstr_fd((char *)data_id->id, log_fd);
	ft_putchar_fd('\n', log_fd);
}

/**
 * @brief Logs that an image path has been found.
 *
 * @param img_path The found image path.
 * @param src_file The source file calling this function.
 * @param src_line The source line calling this function.
 */
void	log_found_img(char *img_path, char *src_file, int src_line)
{
	int	log_fd;

	if (!img_path || !src_file)
	{
		log_msg(WARNING, __FILE__, __LINE__, LOG_INVALID_PARAM);
		return ;
	}
	log_fd = log_start(INFO, src_file, src_line);
	if (log_fd >= 0)
	{
		ft_putstr_fd("FOUND: '", log_fd);
		ft_putstr_fd(img_path, log_fd);
		ft_putendl_fd("'", log_fd);
	}
}

/**
 * @brief Logs that a color definition has been found.
 *
 * @param color The found color value.
 * @param src_file The source file calling this function.
 * @param src_line The source line calling this function.
 */
void	log_found_color(int color, char *src_file, int src_line)
{
	int	log_fd;

	if (!src_file)
	{
		log_msg(WARNING, __FILE__, __LINE__, LOG_INVALID_PARAM);
		return ;
	}
	log_fd = log_start(INFO, src_file, src_line);
	if (log_fd < 0)
		return ;
	ft_putstr_fd("FOUND: r:", log_fd);
	ft_putnbr_fd(get_color_channel(color, RED_CH), log_fd);
	ft_putstr_fd(", g:", log_fd);
	ft_putnbr_fd(get_color_channel(color, GREEN_CH), log_fd);
	ft_putstr_fd(", b:", log_fd);
	ft_putnbr_fd(get_color_channel(color, BLUE_CH), log_fd);
	ft_putendl_fd("", log_fd);
}
