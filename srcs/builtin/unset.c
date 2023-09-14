/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:13:55 by hhino             #+#    #+#             */
/*   Updated: 2023/09/14 19:52:00 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*search_envlist_for_unset(t_info *status, char *str)
{
	d_printf("[search_envlist_forunset]");
	t_list	*env;
	int		len;
	char	*searched_word;

	env = status->env;
	if (!env)
		return (NULL);
	searched_word = ft_strjoin(str, "=");
	len = ft_strlen(searched_word);
	d_printf("[%s:%d]",searched_word,len);
	while (env->next != NULL)
	{
		if (ft_strncmp(env->next->content, searched_word, len) == 0)
			break ;
		if (ft_strncmp(env->next->content, str, len) == 0)
			break ;
		env = env->next;
	}
	if (env->next == NULL) //修正する
	{
		if (ft_strncmp(env->content, searched_word, len) == 0)
			return (env) ;
		if (ft_strncmp(env->content, str, len) == 0)
			return (env) ;
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
		envlist = search_envlist_for_unset(status, ft_strdup(list->content));
		if (envlist != NULL)
		{
			ft_printf("\n\n[[[unset]]]%s\n", list->content);
			temp = envlist;
			envlist->next = envlist->next->next;
			free(temp->content);
			free(temp->next);
			free(temp);
		}
		list = list->next;
	}
}
