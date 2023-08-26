#include "minishell.h"

void	make_env_list(t_info *status, char *env[])
{
	int				i;
	t_libft_list	*newlist;
	t_libft_list	*envlist;

	i = 0;
	envlist = NULL;
	while (env[i] != NULL)
	{
		newlist = ft_lstnew(env[i]);
		if (!newlist)
		{
			status->error = 1;
			return ;
		}
		ft_lstadd_back(&envlist, newlist);
		i++;
	}
	status->env = envlist;
}
