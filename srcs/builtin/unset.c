/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:13:55 by hhino             #+#    #+#             */
/*   Updated: 2023/09/13 21:03:36 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ex_unset(t_info *status, t_stack *data)
{
	t_list	*list;
	t_list	*envlist;
	t_list	*temp;

	list = data->cmdlist->next;
	envlist = status->env;
	while (list != NULL)
	{
		if (search_envlist(status, ft_strdup(list->content)))
		{
			temp = list;
			list->next = list->next->next;
			free(temp);
		}
		list = list->next;
	}
}
