/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_logger.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 19:29:44 by vpoka             #+#    #+#             */
/*   Updated: 2025/11/23 18:19:43 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/common/logging.h"

/**
 * @brief Allocates memory for an array of elements with logging capabilities.
 *
 * This function wraps the standard calloc function to allocate memory for an
 * array of nmemb elements of size bytes each, while providing logging for
 * allocation failures. The memory is initialized to zero. If the allocation
 * fails, an error message is logged with the file and line information.
 *
 * @param nmemb Number of elements to allocate.
 * @param size Size in bytes of each element.
 * @param file Source file name where the allocation is called (for logging).
 * @param line Line number in the source file (for logging).
 * @return Pointer to the allocated memory, or NULL if allocation fails.
 * @note The allocated memory must be freed using free() when no longer needed.
 * @warning If allocation fails, an ERROR level log message is generated and
 *          NULL is returned. The caller should check the return value.
 * @see ft_calloc()
 * @see log_msg()
 */
void	*log_calloc(size_t nmemb, size_t size, const char *file, int line)
{
	void	*ptr;

	ptr = ft_calloc(nmemb, size);
	if (!ptr)
		log_msg(ERROR, file, line, LOG_ALLOC_FAIL);
	return (ptr);
}

/**
 * @brief Reads a line from a file descriptor with logging capabilities.
 *
 * This function wraps the get_next_line function to read a line from the
 * specified file descriptor while providing logging for the operation. It logs
 * a DEBUG message when the function is called and a WARNING message if the
 * function returns NULL (indicating end of file or error).
 *
 * @param file_fd File descriptor to read from.
 * @param file Source file name where the function is called (for logging).
 * @param line Line number in the source file (for logging).
 * @return Pointer to the line read from the file descriptor, or NULL if
 *         end of file is reached or an error occurs.
 * @note The returned string must be freed by the caller when no longer needed.
 * @warning If get_next_line returns NULL, a WARNING level log message is
 *          generated. This could indicate end of file or a read error.
 * @see get_next_line()
 * @see log_msg()
 */
char	*log_get_next_line(int file_fd, char *src_file, int src_line)
{
	char	*line;

	log_msg(DEBUG, src_file, src_line, "calling get_next_line()");
	line = get_next_line(file_fd);
	if (!line)
		log_msg(DEBUG, src_file, src_line, "get_next_line() returned NULL");
	return (line);
}
