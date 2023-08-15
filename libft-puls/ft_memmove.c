/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:06:41 by tokazaki          #+#    #+#             */
/*   Updated: 2023/07/12 11:26:00 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*d;
	const char	*s;

	if (dst == NULL || src == NULL)
		return (NULL);
	d = (char *)dst;
	s = (const char *)src;
	if (d < s)
		return (ft_memcpy(dst, src, len));
	while (len--)
		d[len] = s[len];
	return (dst);
}
//基本的にはmemcpyと一緒だが、cpy先とcoy元が重複していた場合、
//coyミスが起こらないようにcoy開始位置を調整(l,24)
