/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 11:09:45 by tokazaki          #+#    #+#             */
/*   Updated: 2023/08/24 18:43:51 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_libft_list	*ft_lstnew(void *content)
{
	t_libft_list	*result;

	result = (t_libft_list *)malloc(sizeof(t_libft_list) * 1);
	if (result == NULL)
		return (NULL);
	result->content = content;
	result->next = NULL;
	return (result);
}
//新しい構造体を一つ作って、contentを入れて、アドレスを返す
//19:構造体１つ分malloc
//22:content に中身を入れる
//23:nextの中身はないからNULL
//24:アドレスを返す
