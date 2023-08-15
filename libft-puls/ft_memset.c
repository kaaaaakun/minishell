/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:57:29 by tokazaki          #+#    #+#             */
/*   Updated: 2023/07/12 11:27:36 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char	*dest;

	if (!b)
		return (NULL);
	dest = (char *)b;
	while (len--)
	{
		*dest = (char)c;
		dest++;
	}
	return (b);
}
//ある文字列をある文字でlen文字分埋める関数
