/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:41:29 by tokazaki          #+#    #+#             */
/*   Updated: 2023/09/27 14:43:29 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_env_list(t_info *status, char *env[])
{
	int				i;
	t_list	*envlist;

	i = 0;
	envlist = NULL;
	while (env[i] != NULL)
	{
		push_back(&envlist, ft_strdup(env[i]));
		i++;
	}
	status->env = envlist;
}

char	*search_env(t_info *status, char *str)
{
	d_printf("[search_env]");
	t_list	*env;
	char	*searched_word;
	int		len;

	env = status->env;
	if (!env)
		return (NULL);
	searched_word = ft_strjoin(str, "=");
	//status->error
	len = ft_strlen(searched_word);
	d_printf("[%s:%d : %s]",searched_word,len,env->content);
	while (env != NULL) //最後まで行った時を考えて->nextではない方がいい？
	{
//	ft_printf("[%s:%d : %s]\n",searched_word,len,env->content);
		if (ft_strncmp(env->content, searched_word, len) == 0)
			break ;
		env = env->next;
	}
	free (searched_word);
	if (env == NULL)
		return (NULL);
	return (&env->content[len]);
}

t_list	*search_envlist_for_export(t_info *status, char *str)
{
	d_printf("[search_envlist_forexport]");
	t_list	*env;
	int		len;
	char	*searched_word;

	env = status->env;
	if (!env)
		return (NULL);
	//status->error
	searched_word = ft_strjoin(str, "=");
	len = ft_strlen(searched_word);
	d_printf("[%s:%d]",searched_word,len);
	while (env != NULL)
	{
		if (ft_strncmp(env->content, searched_word, len) == 0)
			break ;
		if (ft_strncmp(env->content, str, len) == 0)
			break ;
		env = env->next;
	}
	free (searched_word);
	return (env);
}

t_list	*search_envlist(t_info *status, char *str)
{
	d_printf("[search_envlist]");
	t_list	*env;
	char	*searched_word;
	int		len;

	env = status->env;
	if (!env)
		return (NULL);
	searched_word = ft_strjoin(str, "=");
	//status->error
	len = ft_strlen(searched_word);
	d_printf("[%s:%d]",searched_word,len);
	while (env != NULL)
	{
		if (ft_strncmp(env->content, searched_word, len) == 0)
			break ;
		env = env->next;
	}
	return (env);
}
