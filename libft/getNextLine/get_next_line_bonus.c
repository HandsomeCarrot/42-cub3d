/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:08:31 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/21 02:05:19 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/**
 * @brief Safely frees a dynamically allocated char* and sets to NULL.
 *
 * This function checks if the provided double pointer and the string it points
 * to are valid before attempting to free the memory. If both conditions are
 * met, it frees the allocated memory and sets the pointer to NULL to prevent
 * dangling pointer issues.
 *
 * @param str Double pointer to the string to be freed. If NULL or points to
 *            NULL, the function does nothing.
 *
 * @note This function is particularly useful for managing dynamically
 *       allocated strings in the get_next_line implementation to prevent
 *       memory leaks and ensure proper cleanup.
 */
static void	del_str(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
}

/**
 * @brief Free and clear a dynamically allocated string used by get_next_line.
 *
 * This internal helper frees the memory pointed to by *content (if non-NULL)
 * and sets *content to NULL to prevent dangling pointers. It is safe to call
 * with a NULL pointer or when *content is already NULL.
 *
 * @param content Address of the char* that points to the allocated buffer to
 *                be freed and nulled.
 */
static void	del_content(char **content)
{
	int	i;

	i = 0;
	while (i < MAX_FD)
	{
		del_str(content + i);
		i++;
	}
}

/**
 * @brief Reads from fd until a newline character is found in content.
 *
 * This function continuously reads from the specified file descriptor in chunks
 * of BUFFER_SIZE bytes until either a newline character is found in the
 * accumulated content or an error/end-of-file condition occurs. It appends
 * each read chunk to the existing content using string concatenation.
 *
 * @param fd File descriptor to read from. Must be a valid, open file descriptor.
 * @param content Double pointer to the accumulated content buffer. This buffer
 *                is dynamically allocated and may be modified during the
 *                reading process.
 *
 * @return 0 if reading completes successfully (either newline found or EOF),
 *         1 if a read error occurs (e.g., invalid file descriptor or I/O error).
 *
 * @note The function allocates a temporary buffer for reading and properly
 *       handles memory cleanup in case of errors.
 * @warning If BUFFER_SIZE is too small, this function may perform multiple
 *          read operations which could impact performance for large files.
 */
static int	read_till_newline(int fd, char **content)
{
	ssize_t	bytes_read;
	char	*buffer;
	char	*temp;

	if (gnl_strchr(*content, '\n'))
		return (0);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (1);
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = gnl_strjoin(*content, buffer);
		del_str(content);
		*content = temp;
		if (!temp || gnl_strchr(buffer, '\n'))
			break ;
	}
	del_str(&buffer);
	if (bytes_read < 0)
		return (1);
	return (0);
}

/**
 * @brief Extracts a complete line from the accumulated content buffer.
 *
 * This function searches for the first newline character in the content buffer.
 * If no newline is found, it returns the entire content as a complete line
 * (indicating end-of-file). If a newline is found, it extracts the substring
 * from the beginning up to and including the newline character, then updates
 * the content buffer to contain only the remaining text after the newline.
 *
 * @param content Double pointer to the accumulated content buffer. This buffer
 *                is modified to remove the extracted line portion.
 *
 * @return Pointer to a newly allocated string containing the extracted line,
 *         including the newline character if present. Returns NULL if content
 *         is NULL or empty, or if memory allocation fails.
 *
 * @note The returned string is dynamically allocated and must be freed by the
 *       caller. The original content buffer is modified to remove the
 *       extracted portion.
 * @warning If memory allocation fails during the substring operations, the
 *          function may return NULL and the content buffer may be left in an
 *          inconsistent state.
 */
static char	*get_line(char **content)
{
	char	*newline_pos;
	char	*line;
	char	*tmp;

	if (!content || !*content)
		return (NULL);
	newline_pos = gnl_strchr(*content, '\n');
	if (!newline_pos)
	{
		line = gnl_strdup(*content);
		del_str(content);
		return (line);
	}
	tmp = gnl_strdup(newline_pos + 1);
	if (!tmp)
		return (NULL);
	line = gnl_substr(*content, 0, (newline_pos - *content + 1));
	del_str(content);
	*content = tmp;
	return (line);
}

/**
 * @brief Reads the next line from a file descriptor.
 *
 * This is the main entry point for the get_next_line function. It reads from
 * the specified file descriptor and returns the next line of text, handling
 * multiple calls to read through a file by maintaining static state between
 * calls. The function reads in chunks defined by BUFFER_SIZE and accumulates
 * content until a complete line (ending with newline or EOF) is available.
 *
 * @param fd File descriptor to read from. Must be a valid, open file descriptor
 *           with read permissions.
 *
 * @return Pointer to a dynamically allocated string containing the next line
 *         from the file, including the newline character if present. Returns
 *         NULL when end-of-file is reached, if an error occurs, or if invalid
 *         parameters are provided.
 *
 * @note The returned string must be freed by the caller. The function uses
 *       static storage to maintain state between calls, allowing it to
 *       continue reading from where it left off in subsequent calls.
 * @warning This function uses an array-based approach to handle multiple
 *          file descriptors simultaneously, making it suitable for bonus
 *          requirements.
 * @see read_till_newline(), get_line(), del_str()
 */
char	*get_next_line(int fd)
{
	static char	*content[MAX_FD];
	char		*result;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0 || MAX_FD <= 0)
		return (del_content(content), NULL);
	if (read_till_newline(fd, content + fd))
		return (del_str(content + fd), NULL);
	result = get_line(content + fd);
	if (!result || !*result)
		return (del_str(content + fd), NULL);
	return (result);
}
