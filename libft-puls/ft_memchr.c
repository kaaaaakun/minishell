/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:15:00 by tokazaki          #+#    #+#             */
/*   Updated: 2023/07/12 11:19:25 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*str;
	char	chr;

	if (s == NULL)
		return (NULL);
	chr = (char)c;
	str = (char *)s;
	while (n--)
	{
		if (*str == chr)
			return (str);
		str++;
	}
	return (NULL);
}
//ある文字cが使われている場所を返す関数
//20,文字列がNULLは無処理
//22-23,キャスト後処理
//24-29,cが使われている場所を探す作業
//30,nが0文字だった場合、NULLを返す
