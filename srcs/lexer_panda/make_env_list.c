/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 19:41:29 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/15 20:18:09 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_pwd__shvl___env(t_info *status)
{
	t_list	*envlist;
	char	*path;
	char	buf[PATH_MAX];

	envlist = NULL;
	path = getcwd(buf, PATH_MAX);
	if (path == NULL)
		exit (1);
	push_back(&envlist, ft_strjoin_free("PWD=", path, NEITHER_FREE));
	push_back(&envlist, ft_strdup("SHLVL=1"));
	push_back(&envlist, ft_strdup("_=/usr/bin/env"));
	status->env = envlist;
}

void	make_env_list(t_info *status, char *env[])
{
	int		i;
	t_list	*envlist;

	i = 0;
	envlist = NULL;
	while (env[i] != NULL)
	{
		push_back(&envlist, ft_strdup(env[i]));
		i++;
	}
	status->env = envlist;
	if (envlist == NULL)
		make_pwd__shvl___env(status);
}

char	*search_env(t_info *status, char *str)
{
	t_list	*env;
	char	*searched_word;
	int		len;

	d_printf("[search_env]");
	env = status->env;
	if (!env)
		return (NULL);
	searched_word = ft_strjoin_free(str, "=", NEITHER_FREE);
	len = ft_strlen(searched_word);
	d_printf("[%s:%d : %s]", searched_word, len, env->content);
	while (env != NULL)
	{
		d_printf("[%s:%d : %s]\n", searched_word, len, env->content);
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
	t_list	*env;
	int		len;
	char	*searched_word;

	d_printf("[search_envlist_forexport]");
	env = status->env;
	if (!env)
		return (NULL);
	searched_word = ft_strjoin_free(str, "=", NEITHER_FREE);
	len = ft_strlen(searched_word);
	d_printf("[%s:%d]", searched_word, len);
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
	t_list	*env;
	char	*searched_word;
	int		len;

	d_printf("[search_envlist]");
	env = status->env;
	if (!env)
		return (NULL);
	searched_word = ft_strjoin_free(str, "=", NEITHER_FREE);
	len = ft_strlen(searched_word);
	d_printf("[%s:%d]", searched_word, len);
	while (env != NULL)
	{
		if (ft_strncmp(env->content, searched_word, len) == 0)
			break ;
		env = env->next;
	}
	free_null(searched_word);
	return (env);
}
