#include "minishell.h"

void	make_env_list(t_info *status, char *env[])
{
	int				i;
	t_list	*envlist;

	i = 0;
	envlist = NULL;
	while (env[i] != NULL)
	{
		push_back(&envlist, env[i]);
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
	d_printf("[%s:%d]",searched_word,len);
	while (env->next != NULL)
	{
		if (ft_strncmp(env->content, searched_word, len) == 0)
			break ;
		env = env->next;
	}
	if (ft_strncmp(env->content, searched_word, len) != 0)
		return (NULL);
	return (&env->content[len]);
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
	while (env->next != NULL)
	{
		if (ft_strncmp(env->content, searched_word, len) == 0)
			break ;
		env = env->next;
	}
	return (env);
}
