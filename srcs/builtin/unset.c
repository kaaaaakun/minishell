/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:13:55 by hhino             #+#    #+#             */
/*   Updated: 2023/10/13 20:52:26 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"

// bash only deletes when only the left side matches,
// but this also deletes when the left side matches or
// the left side and right side match perfectly.

static void	unset_top_list(t_info *status, t_list *envlist)
{
	t_list	*temp;

	temp = envlist;
	status->env = envlist->next;
	free_t_list(temp);
}

static void	core_of_unset(t_info *status, char *dup_content)
{
	t_list	*temp;
	t_list	*envlist;

	if (search_envlist_for_export(status, dup_content) != NULL)
	{
		envlist = search_envlist_for_export(status, dup_content);
		if (unset_the_top_or_not(status, dup_content) == 1)
			unset_top_list(status, envlist);
		else if (envlist->next == NULL)
		{
			temp = envlist;
			envlist = search_envlist_for_unset(status, dup_content);
			envlist->next = NULL;
			free_t_list(temp);
		}
		else if (envlist->next != NULL)
		{
			temp = envlist;
			envlist = search_envlist_for_unset(status, dup_content);
			envlist->next = envlist->next->next;
			free_t_list(temp);
		}
	}
}

void	ex_unset(t_info *status, t_stack *data)
{
	t_list	*list;
	char	*dup_content;

	list = data->cmdlist->next;
	while (list != NULL)
	{
		dup_content = ft_strdup(list->content);
		core_of_unset(status, dup_content);
		free(dup_content);
		list = list->next;
	}
	status->exit_status = 0;
}
