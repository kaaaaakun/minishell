/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 17:42:28 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/07 13:45:56 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	char	*result;

	if (!s1)
		return (NULL);
	while (ft_strchr((char *)set, (int)*s1) != 0 && *s1)
		s1++;
	len = ft_strlen((char *)s1);
	if (*s1)
	{
		while (ft_strchr ((char *)set, (int)s1[len - 1]))
			len--;
	}
	result = (char *)ft_calloc(len + 1, sizeof(char));
	if (result == NULL)
		return (NULL);
	return (ft_memcpy(result, s1, len));
}
//文字列*sの前と後ろから*setが含まれる文字を取り除いて残りを返す

char	*ft_strtrim_free(char const *s1, char const *set, int free_flag)
{
	char	*trimed_str;

	trimed_str = ft_strtrim(s1, set);
	if (free_flag == FIRST_FREE || free_flag == BOTH_FREE)
		free((void *)s1);
	if (free_flag == SECOND_FREE || free_flag == BOTH_FREE)
		free((void *)set);
	return (trimed_str);
}
