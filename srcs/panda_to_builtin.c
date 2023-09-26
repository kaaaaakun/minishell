/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panda_to_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 15:44:34 by tokazaki          #+#    #+#             */
/*   Updated: 2023/09/26 16:42:38 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"
#include "builtin.h"

void	check_command(t_info *status, t_stack *data)
{
	d_printf("[check_command]");
	char		*line;

	while (data->next != NULL)
		data = data->next;
	if (data->cmdlist == NULL)
		return ;
	line = data->cmdlist->content;
	d_printf("[line:%s]", line);
	if (ft_memcmp(line, "exit", 5) == 0)
		ex_exit(status, data);
	else if (ft_memcmp(line, "echo", 5) == 0)
		ex_echo(status, data);
	else if (ft_memcmp(line, "env", 4) == 0)
		ex_env(status, data);
	else if (ft_memcmp(line, "cd", 3) == 0)
		ex_cd(status, data);
	else if (ft_memcmp(line, "pwd", 4) == 0)
		ex_pwd();
	else if (ft_memcmp(line, "export", 7) == 0)
		ex_export(status, data);
	else if (ft_memcmp(line, "unset", 6) == 0)
		ex_unset(status, data);
	else
	{
		usleep(100);
		d_printf(ft_strjoin("builtin not found: ", line));
		ex_execve(status);
	}
	if (status->pid == 1)
		exit(0);
	rl_on_new_line();
//	split_free(split);
}

