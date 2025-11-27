/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <vpoka@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:09:01 by vpoka             #+#    #+#             */
/*   Updated: 2025/10/21 01:15:24 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/**
 * @brief Calculate the length of a null-terminated string.
 *
 * This function computes the length of the input string by counting
 * characters until the null terminator is encountered. It safely
 * handles NULL pointers by returning 0.
 *
 * @param s Pointer to the null-terminated string to measure.
 * @return The number of characters in the string (excluding the null
 *         terminator). Returns 0 if the input pointer is NULL.
 */
size_t	gnl_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s && s[len])
		len++;
	return (len);
}

/**
 * @brief Create a duplicate of a null-terminated string.
 *
 * This function allocates memory for a copy of the input string and
 * copies the content character by character. The caller is responsible
 * for freeing the returned memory.
 *
 * @param s Pointer to the null-terminated string to duplicate.
 * @return Pointer to the newly allocated string copy, or NULL if
 *         memory allocation fails or input is NULL.
 * @note The returned string must be freed by the caller to avoid
 *       memory leaks.
 */
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

/**
 * @brief Concatenate two null-terminated strings into a new string.
 *
 * This function creates a new string by concatenating s1 and s2.
 * It allocates memory for the result and copies both strings
 * sequentially. Handles NULL inputs gracefully by treating them as
 * empty strings.
 *
 * @param s1 First null-terminated string to concatenate.
 * @param s2 Second null-terminated string to concatenate.
 * @return Pointer to the newly allocated concatenated string, or NULL
 *         if memory allocation fails. Returns an empty string if both
 *         inputs are NULL or empty.
 * @note The returned string must be freed by the caller to avoid
 *       memory leaks.
 */
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

/**
 * @brief Locate the first occurrence of a character in a string.
 *
 * This function searches for the first occurrence of the character c
 * (converted to char) in the string s. The search includes the null
 * terminator if c is specified as '\0'.
 *
 * @param s Pointer to the null-terminated string to search.
 * @param c Character to locate (converted to char).
 * @return Pointer to the first occurrence of c in s, or NULL if the
 *         character is not found or input string is NULL.
 * @note This function can locate the null terminator if c is '\0'.
 */
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

/**
 * @brief Extract a substring from a string.
 *
 * This function creates a new string containing a portion of the
 * original string starting at position start and extending for at
 * most len characters. If start is beyond the string length, returns
 * an empty string. If len exceeds available characters, copies only
 * the available portion.
 *
 * @param s Pointer to the source null-terminated string.
 * @param start Starting position in the source string (0-indexed).
 * @param len Maximum number of characters to extract.
 * @return Pointer to the newly allocated substring, or NULL if memory
 *         allocation fails or input string is NULL. Returns empty
 *         string if start is beyond string length.
 * @note The returned string must be freed by the caller to avoid
 *       memory leaks.
 * @warning If start position is beyond the string length, an empty
 *          string is returned rather than NULL.
 */
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
