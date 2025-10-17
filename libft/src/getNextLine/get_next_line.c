/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:08:31 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/17 20:41:07 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	del_str(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

static char	*fill_content(int fd, char **content)
{
	ssize_t	read_size;
	char	*buffer;
	char	*temp;
	int		i;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	read_size = read(fd, buffer, BUFFER_SIZE);
	i = 1;
	while (read_size > 0)
	{
		buffer[read_size] = '\0';
		temp = gnl_ft_strjoin(*content, buffer);
		del_str(content);
		*content = temp;
		if (!temp || (i && gnl_ft_strchr(*content, '\n'))
			|| (!i && gnl_ft_strchr(buffer, '\n')))
			break ;
		read_size = read(fd, buffer, BUFFER_SIZE);
		i = 0;
	}
	if (read_size < 0)
		return (del_str(&buffer), NULL);
	return (del_str(&buffer), *content);
}

static char	*fill_result(char **content)
{
	char	*trimed;
	char	*start;
	char	*end;

	start = *content;
	end = gnl_ft_strchr(start, '\n');
	if (!end)
	{
		trimed = NULL;
		if (start && *start)
			trimed = gnl_ft_strdup(start);
		del_str(content);
		return (trimed);
	}
	trimed = gnl_ft_strdup(end + 1);
	if (!trimed)
		return (NULL);
	*content = trimed;
	trimed = gnl_ft_substr(start, 0, (end - start + 1));
	del_str(&start);
	return (trimed);
}

char	*get_next_line(int fd)
{
	static char	*content;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!fill_content(fd, &content))
		return (del_str(&content), NULL);
	result = fill_result(&content);
	if (!result || !(*result))
		return (del_str(&content), NULL);
	return (result);
}
