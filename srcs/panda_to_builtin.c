/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panda_to_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 15:44:34 by tokazaki          #+#    #+#             */
/*   Updated: 2023/09/18 13:28:48 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"
#include "builtin.h"

void	check_command(t_info *status, t_stack *data)
{
	ft_putstr_fd("[check_command]", 1);
	char		 *line;

	if (data->cmdlist == NULL)
		return ;
	line = data->cmdlist->content;
	d_printf("[line:%s]",line);
	if (ft_memcmp(line, "exit", 5) == 0)
		ex_exit(0);
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
		ft_putendl_fd(ft_strjoin("builtin not found: ", line), 1);
//		char *cat[] = {"cat", "-n", NULL};
//		execve("/bin/cat", cat ,NULL);
		ex_execve(status);
//		ex_execve(split, pipe_flag, status);  listを**にする関数
	}
	rl_on_new_line();
//	split_free(split);
}

