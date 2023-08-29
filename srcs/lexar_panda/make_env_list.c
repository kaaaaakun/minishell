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
