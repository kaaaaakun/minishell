/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 09:08:19 by hhino             #+#    #+#             */
/*   Updated: 2023/09/04 20:11:42 by hhino            ###   ########.fr       */
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

void	free_list(t_list *head)
{
	t_list	*temp;

	while (head != NULL)
	{
		temp = head;
		free(temp);
		head = head->next;
	}
}

void	free_stack(t_stack *stack)
{
	free_list(stack->outputlist);
	free_list(stack->appendlist);
	free_list(stack->inputlist);
	free_list(stack->heredoclist);
	free_list(stack->cmdlist);
	stack->next = NULL;
}
//これでstackの中身全てnullになっている
