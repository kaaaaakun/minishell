/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:25:09 by tokazaki          #+#    #+#             */
/*   Updated: 2023/09/05 17:00:42 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"


void	wait_process(t_info *info_status)
{
	int	i;
	int	status;

	ft_printf("[wait;%d]", info_status->exec_count);
	i = 1;
	while (i < info_status->exec_count)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) != 0)
			;
		i++;
	}
	waitpid(info_status->pid, &status, 0);
	if (WEXITSTATUS(status) != 0)
		;
}

void	check_command(t_info *status, t_stack *data)
{
	ft_putstr_fd("[check_command]", 1);
	char		 *line;

	line = data->cmdlist->content;
	ft_printf("[line:%s]",line);
	if (ft_memcmp(line, "exit", 5) == 0)
		ex_exit(0);
	else if (ft_memcmp(line, "echo", 5) == 0)
		ex_echo(status, data);
	else if (ft_memcmp(line, "env", 4) == 0)
		ex_env();
	else if (ft_memcmp(line, "cd", 3) == 0)
		ex_cd(status, data);
	else if (ft_memcmp(line, "pwd", 4) == 0)
		ex_pwd();
	else if (ft_memcmp(line, "export", 7) == 0)
		ex_export(status, data);
	else
	{
		usleep(100);
		ft_putendl_fd(ft_strjoin("builtin not found: ", line), 1);
//		ex_execve(split, pipe_flag, status);
	}
	rl_on_new_line();
//	split_free(split);
}

void	check_line(char *line, t_info *status)
{
	ft_putstr_fd("[check_line]", 1);

	if (line && *line)
		add_history(line);
	ft_printf("[check_line:%d]", status->exec_count);
	if (!line)
		ex_exit(0);
	status->exec_count = 0;
	if (*line == '\0')
	{
		ft_putstr_fd("", 1);
		rl_on_new_line();
		return ;
	}
	int			cpy_stdin = dup(0);
	panda(line, status);
	debug(status,"panda to check");
	check_command(status, status->stack);
	debug(status,"before free");
	free_stack(status);//
	debug(status,"after free");
//	wait_process(status);
	dup2(cpy_stdin, 0);
//	split_free(splited_pipe);
}

int	main(int argc, char *argv[], char *env[])
{
	char	*line;
	t_info	*status;

	if (argc != 1)
		return (0);
	add_sigaction();
	status = (t_info *)malloc(sizeof(t_info) * 1);
	if (!status)
		ex_exit(0);
	status->exec_count = 0;
	status->error = 0;
	status->stack = 0;
	make_env_list(status, env);
	while (1)
	{
		line = readline("[readline]>> ");
		ft_printf("[%s]", line);
		check_line(line, status);
		free (line);
	}
	(void)argv;
	(void)env;
	return (0);
}
