/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 20:11:54 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/12 20:03:42 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ex_exit_non_pipe(t_info *status, int exit_flag)
{
	if (status->pipe != 0)
		exit (exit_flag);
	dup2(status->cpy_stdout, 1);
	close (status->cpy_stdout);
	ft_printf("exit\n");
}

static void	ex_exit_with_something(t_info *status, t_stack *data)
{
	t_list	*list;

	list = data->cmdlist;
	if (list->next->next != NULL)
	{
		ex_exit_non_pipe(status, 0);
		error_printf(" too many arguments\n");
		exit (1);
	}
	else if (ft_str_is_num(list->next->content) == 1)
	{
		status->exit_status = ft_atoi(list->next->content) % 256;
		ex_exit_non_pipe(status, status->exit_status);
		exit (status->exit_status);
	}
	else if (ft_str_is_num(list->next->content) == 0)
	{
		ex_exit_non_pipe(status, 255);
		error_printf(" numeric argument required\n");
		exit(255);
	}
}

void	ex_exit(t_info *status, t_stack *data)
{
	t_list	*list;

	if (status->line == NULL)
	{
		ex_exit_non_pipe(status, 0);
		exit (0);
	}
	list = data->cmdlist;
	if (list == NULL || status == NULL || list->next == NULL
		|| ft_memcmp(list->next->content, "--", 3) == 0)
	{
		ex_exit_non_pipe(status, 0);
		exit (0);
	}
	ex_exit_with_something(status, data);
}
