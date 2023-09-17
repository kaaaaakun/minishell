/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:13:55 by hhino             #+#    #+#             */
/*   Updated: 2023/09/17 17:11:20 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

//Returns the previous list of matches

static t_list	*search_envlist_for_unset(t_info *status, char *str)
{
	t_list	*env;
	int		len;
	char	*searched_word;

	env = status->env;
	if (!env)
		return (NULL);
	searched_word = ft_strjoin(str, "=");
	len = ft_strlen(searched_word);
	while (env->next != NULL)
	{
		if (ft_strncmp(env->next->content, searched_word, len) == 0)
			break ;
		else if (ft_strncmp(env->next->content, str, len) == 0)
			break ;
		env = env->next;
	}
	if (env->next == NULL)
	{
		if (ft_strncmp(env->content, searched_word, len) != 0)
			return (NULL);
		else if (ft_strncmp(env->content, str, len) != 0)
			return (NULL);
	}
	return (env);
}

//bash only deletes when only the left side matches,
//but this also deletes when the left side matches or
//the left side and right side match perfectly.

void	ex_unset(t_info *status, t_stack *data)
{
	t_list	*list;
	t_list	*envlist;
	// t_list	*temp;

	list = data->cmdlist->next;
	while (list != NULL)
	{
		if (search_envlist_for_export(status, ft_strdup(list->content)) != NULL)
		{
			envlist = search_envlist_for_export(status, ft_strdup(list->content));
			if (envlist->next == NULL)
			{
				envlist = search_envlist_for_unset(status, ft_strdup(list->content));
				// temp = envlist->next;
				envlist->next = NULL;
				// free(temp->content);
				// free(temp->next);
				// free(temp);
			}
			else if (envlist->next != NULL)
			{
				envlist = search_envlist_for_unset(status, ft_strdup(list->content));
				// temp = envlist->next;
				envlist->next = envlist->next->next;
				// free(temp->content);
				// free(temp->next);
				// free(temp);
			}
		}
		list = list->next;
	}
}
