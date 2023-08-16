/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:26:28 by tokazaki          #+#    #+#             */
/*   Updated: 2023/06/10 20:12:50 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	if (dst == NULL && src == NULL)
		return (NULL);
	d = dst;
	s = src;
	while (n--)
		*d++ = *s++;
	return (dst);
}

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	char	chr;

	if (!s)
		return (NULL);
	str = (char *)s;
	chr = (char)c;
	while (*str || chr == '\0')
	{
		if (*str == chr)
			return (str);
		str++;
	}
	return (NULL);
}

char	*ft_strdup(const char *src)
{
	char	*result;

	if (!src)
		return (NULL);
	result = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (result == 0)
		return (NULL);
	ft_memcpy(result, src, (ft_strlen(src) + 1));
	return (result);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	length;
	char			*result;
	char			*str;

	str = (char *)s;
	if (s == NULL)
		return (NULL);
	length = ft_strlen((char *)s);
	if (len == 0 || length <= start)
		return (ft_strdup (""));
	length = ft_strlen(&str[start]);
	if (len < length)
		length = len;
	result = (char *)malloc((length + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	result[length] = '\0';
	return (ft_memcpy(result, &str[start], length));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	s1_len;
	size_t	s2_len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen((char *)s1);
	s2_len = ft_strlen((char *)s2);
	result = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	ft_memcpy (result, s1, s1_len);
	ft_memcpy (&result[s1_len], s2, s2_len);
	result[s1_len + s2_len] = '\0';
	return (result);
}
