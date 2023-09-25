/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_libft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 18:28:29 by hhino             #+#    #+#             */
/*   Updated: 2023/09/25 18:29:00 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_panda.h"
#include "minishell.h"
#include <errno.h>

void	*mini_memcpy(void *dst, const void *src, size_t n)
{
	char		*d;
	const char	*s;
	int			flag;

	flag = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	d = dst;
	s = src;
	while (n--)
	{
		if ((*s == '\'' || *s == '\"') && !(flag & IN_QUOTE))
		{
			plusle_quote(*s, &flag);
			s++;
		}
		if ((*s == '\'' && flag & S_QUOTE) || (*s == '\"' && flag & D_QUOTE))
		{
			minun_quote(*s, &flag);
			s++;
		}
		*d++ = *s++;
	}
	return (dst);
}

char	*mini_substr(char const *s, unsigned int start, size_t len)
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
	result = (char *)ft_calloc(length + 1, sizeof(char));
	if (result == NULL)
		return (NULL);
	return (mini_memcpy(result, &str[start], length));
}
