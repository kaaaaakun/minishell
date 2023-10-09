/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 09:08:19 by hhino             #+#    #+#             */
/*   Updated: 2023/10/09 14:39:36 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"

t_list	*create_list(char *str)
{
	t_list	*newlist;

	if (!str)
		return (NULL);
	newlist = (t_list *)malloc_ee(sizeof(t_list));
	if (!newlist)
		return (NULL);
	newlist->content = str;
	newlist->flag = 0;
	newlist->next = NULL;
	return (newlist);
}

void	push_back(t_list **head, char *str)
{
	t_list	*newlist;
	t_list	*current;

	newlist = create_list(str);
	if (!newlist || !str)
		return ;
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

	d_printf("free adress:%p", head);
	while (head != NULL)
	{
		temp = head->next;
		free(head->content);
		free(head);
		head = NULL;
		head = temp;
	}
}

size_t	listsize(t_list *lst)
{
	size_t	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	free_stack(t_info *status)
{
	t_stack	*data;
	t_stack	*tmp;

	data = status->stack;
	while (data != NULL)
	{
		free_list(data->outputlist);
		free_list(data->appendlist);
		free_list(data->inputlist);
		free_list(data->heredoclist);
		free_list(data->cmdlist);
		tmp = data->next;
		free(data);
		data = tmp;
	}
	status->stack = NULL;
}
