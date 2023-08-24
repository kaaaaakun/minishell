/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 11:43:02 by tokazaki          #+#    #+#             */
/*   Updated: 2023/08/24 18:43:41 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_libft_list **lst, void (*del)(void*))
{
	t_libft_list	*tmp;
	t_libft_list	*ptr;

	if (lst == NULL || del == NULL)
		return ;
	ptr = *lst;
	while (ptr)
	{
		tmp = ptr->next;
		ft_lstdelone(ptr, del);
		ptr = tmp;
	}
	*lst = NULL;
}
//構造体の先頭アドレスを渡すと全てfreeする関数
//20:エラー処理
//22:*lst を保存しておくためにptrを用いる
//25,27:nextのアドレスを一時的に保持、その後改めて使う
//26:fr_deloneで1つの構造体をfreeする
//29:*lstのアドレスにNULLを入れる
