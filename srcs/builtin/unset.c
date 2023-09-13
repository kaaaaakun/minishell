/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:13:55 by hhino             #+#    #+#             */
/*   Updated: 2023/09/13 20:56:49 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ex_unset(t_info *status, t_stack *data)
{
	t_list	*list;
	t_list	*envlist;

	list = data->cmdlist->next;
	envlist = status->env;
	while (list != NULL)
	{
		if (search_envlist(status, ft_strdup(list->content)))
		{
			
			free;
		}
		list = list->next;
	}
}
