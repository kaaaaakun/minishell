/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:37:51 by tokazaki          #+#    #+#             */
/*   Updated: 2023/09/17 16:20:08 by hhino            ###   ########.fr       */
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
	(void)data;
	write_env(status->env);
}
