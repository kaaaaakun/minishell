/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 09:08:19 by hhino             #+#    #+#             */
/*   Updated: 2023/09/02 21:59:41 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"

t_list	*create_list(char *str)
{
	t_list	*newlist;

	newlist = (t_list *)malloc(sizeof(t_list));
	if (!newlist)
		return (NULL);
	newlist->content = str;
	newlist->next = NULL;
	return (newlist);
}

void	push_back(t_list **head, char *str)
{
	t_list	*newlist;
	t_list	*current;

	newlist = create_list(str);
	if (!newlist || !str)
		return ; //子プロセスのみ終了したい
	if (*head == NULL)
	{
		*head = newlist;
		return ;
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = newlist;
}
