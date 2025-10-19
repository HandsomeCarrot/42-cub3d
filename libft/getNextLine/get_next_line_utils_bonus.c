/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:09:01 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/19 10:05:52 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	gnl_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s && s[len])
		len++;
	return (len);
}

char	*gnl_strdup(const char *s)
{
	int		s_len;
	char	*str;
	int		pos;

	s_len = gnl_strlen(s);
	str = malloc(s_len * sizeof(char) + 1);
	if (!str || !s)
		return (NULL);
	pos = 0;
	while (pos <= s_len)
	{
		str[pos] = s[pos];
		pos++;
	}
	return (str);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	result_len;
	size_t	pos;

	result_len = gnl_strlen(s1) + gnl_strlen(s2);
	if (result_len == 0)
		return (gnl_strdup(""));
	result = malloc((result_len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	pos = 0;
	while (s1 && s1[pos])
	{
		result[pos] = s1[pos];
		pos++;
	}
	while (s2 && *s2)
	{
		result[pos] = *s2;
		s2++;
		pos++;
	}
	result[pos] = '\0';
	return (result);
}

char	*gnl_strchr(const char *s, int c)
{
	char	*result;

	result = (char *)s;
	while (result && *result)
	{
		if (*result == (char)c)
			return (result);
		result++;
	}
	if (result && *result == (char)c)
		return (result);
	return (NULL);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	char			*res;
	size_t			pos;
	unsigned int	s_len;
	int				res_len;

	if (!s)
		return (NULL);
	s_len = gnl_strlen(s);
	if (start >= s_len)
		return (gnl_strdup(""));
	res_len = len;
	if (len > s_len - start)
		res_len = s_len - start;
	res = malloc(res_len * sizeof(char) + 1);
	if (!res)
		return (res);
	pos = 0;
	while (pos < len && s[start + pos])
	{
		res[pos] = s[start + pos];
		pos++;
	}
	res[pos] = '\0';
	return (res);
}
