/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:13:55 by hhino             #+#    #+#             */
/*   Updated: 2023/09/15 16:48:14 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*search_envlist_for_unset(t_info *status, char *str)
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
	return (env);
}

void	ex_unset(t_info *status, t_stack *data)
{
	t_list	*list;
	t_list	*temp;
	t_list	*envlist;

	list = data->cmdlist->next;
	while (list != NULL)
	{
		if (search_envlist_for_export(status, ft_strdup(list->content)))
		{
			envlist = search_envlist_for_export(status, ft_strdup(list->content));
			if (envlist->next == NULL)
			{
				ft_printf("\n\n[[[unset]]]%s\n", list->content);
				temp = envlist;
				free(temp->content);
				free(temp->next);
				// free(temp);
				temp = NULL;
			}
			else if (envlist->next != NULL)
			{
				envlist = search_envlist_for_unset(status, ft_strdup(list->content));
				ft_printf("\nprev;%s\nnextnext;%s", envlist->content, envlist->next->next->content);
				temp = envlist->next;
				envlist->next = envlist->next->next;
				// free(temp->content);
				// free(temp->next);
				// free(temp);
			}
			list = list->next;
		}
	}
}
