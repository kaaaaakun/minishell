/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 19:30:56 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/09 21:05:05 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*result;

	if (size == 0 || count == 0)
	{
		size = 1;
		count = 1;
	}
	if (size > SIZE_MAX / count)
		return (NULL);
	result = (void *)malloc_ee (size * count);
	if (result == NULL)
		return (NULL);
	ft_bzero(result, size * count);
	return (result);
}

void	*malloc_ee(size_t size)
{
	void		*result;

	result = malloc(size);
	//ft_printf("%p",result);
	return (result);
}
//19:size or count がゼロの時には1byte分
//24:size * count < SIZE_MAX になってしまう場合はNULLを返す
//29:全てを'\0'で埋めて返す
