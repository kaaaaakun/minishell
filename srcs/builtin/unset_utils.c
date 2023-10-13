/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 19:51:46 by hhino             #+#    #+#             */
/*   Updated: 2023/10/13 20:47:48 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"

// Returns the previous list of matches

t_list	*search_envlist_for_unset(t_info *status, char *str)
{
	t_list	*env;
	int		len;
	char	*searched_word;

	env = status->env;
	if (!env)
		return (NULL);
	searched_word = ft_strjoin_free(str, "=", NEITHER_FREE);
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
		unset_the_last_env(str, env, searched_word);
	free(searched_word);
	return (env);
}

int	unset_the_top_or_not(t_info *status, char *str)
{
	t_list	*env;
	int		len;
	char	*searched_word;

	d_printf("[unset_the_top_or_not]");
	env = status->env;
	if (!env)
		return (0);
	searched_word = ft_strjoin_free(str, "=", NEITHER_FREE);
	len = ft_strlen(searched_word);
	if (env != NULL)
	{
		if (ft_strncmp(env->content, str, len) == 0)
		{
			free(searched_word);
			return (1);
		}
		else if (ft_strncmp(env->content, searched_word, len) == 0)
		{
			free(searched_word);
			return (1);
		}
	}
	free(searched_word);
	return (0);
}

t_list	*unset_the_last_env(char *str, t_list *env, char *searched_word)
{
	int	len;

	len = ft_strlen(searched_word);
	if (ft_strncmp(env->content, searched_word, len) != 0)
	{
		free(searched_word);
		return (NULL);
	}
	else if (ft_strncmp(env->content, str, len) != 0)
	{
		free(searched_word);
		return (NULL);
	}
	return (env);
}

void	free_t_list(t_list *temp)
{
	free(temp->content);
	free(temp);
}
