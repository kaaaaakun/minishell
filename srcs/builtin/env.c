/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:37:51 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/11 15:07:01 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_env(t_list *env)
{
	while (env != NULL)
	{
		if (ft_strchr(env->content, '=') != NULL)
			ft_putendl_fd(env->content, 1);
		env = env->next;
	}
}

void	ex_env(t_info *status, t_stack *data)
{
	t_list	*list;

	list = data->cmdlist->next;
	if (list == NULL || ft_memcmp(list->content, "--", 3) == 0)
	{
		write_env(status->env);
		status->exit_status = 0;
	}
	else
	{
		ft_printf("%s: No such file or directory", list->content);
		status->exit_status = 127;
	}
}
