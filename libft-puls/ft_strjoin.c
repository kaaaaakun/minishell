/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 15:09:56 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/08 17:04:53 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	s1_len;
	size_t	s2_len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen((char *)s1);
	s2_len = ft_strlen((char *)s2);
	result = (char *)malloc_ee((s1_len + s2_len + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	ft_memcpy (result, s1, s1_len);
	ft_memcpy (&result[s1_len], s2, s2_len);
	result[s1_len + s2_len] = '\0';
	return (result);
}

char	*ft_strjoin_free(char const *s1, char const *s2, int free_flag)
{
	char	*joined_str;

	joined_str = ft_strjoin(s1, s2);
	if (free_flag == FIRST_FREE || free_flag == BOTH_FREE)
	{
		free((void *)s1);
		s1 = NULL;
	}
	if (free_flag == SECOND_FREE || free_flag == BOTH_FREE)
	{
		free((void *)s2);
		s1 = NULL;
	}
	if (joined_str == NULL)
		exit (1);
	return (joined_str);
	(void)free_flag;
}
