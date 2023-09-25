/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:25:09 by tokazaki          #+#    #+#             */
/*   Updated: 2023/09/25 19:57:38 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"
#include "builtin.h"

void	check_command(t_info *status, t_stack *data);

void	wait_process(t_info *status)
{
	int	i;
	int	exit_status;

	d_printf("[wait;%d]", status->pipe);
	if (status->pipe == 0)
		return ;
	i = 0;
	while (i <= status->pipe)
	{
		waitpid(-1, &exit_status, 0);
		if (WEXITSTATUS(exit_status) != 0)
			;
		i++;
	}
	return ;
	waitpid(status->pid, &exit_status, 0);
	if (WEXITSTATUS(exit_status) != 0)
		;
}

void	check_line(char *line, t_info *status)
{
	ft_putstr_fd("[check_line]", 1);

	if (line && *line)
		add_history(line);
	d_printf("[check_line:%d]", status->exec_count);
	if (!line)
		ex_exit(status, NULL);
	status->exec_count = 0;
	if (*line == '\0')
	{
		ft_putstr_fd("", 1);
		rl_on_new_line();
		return ;
	}
	status->cpy_stdin = dup(0);
	int			cpy_stdout = dup(1);
	panda(line, status);
	if (status->error)
		return ;
	debug(status,"panda to check");
//	if (status->pipe != 0)
//	{
//		int	pid;
//
//		d_printf("last-fork");
//		pid = fork();
//		if (pid < 0)
//			error_exit("fork");
//		if (pid == 0)
//		{
//			status->pid = 1;
//			check_command(status, status->stack);
//		}
//	}
//	else
	if (status->pipe == 0)
	{
		check_command(status, status->stack);
		free_stack(status);
	}
//	wait_process(status);
	dup2(status->cpy_stdin, 0);
	dup2(cpy_stdout, 1);
}

void	reset_status(t_info *status)
{
	status->pid = 0;
	status->pipe = 0;
	status->pre_pipe1 = -1;
	status->pre_pipe0 = -1;
	status->error = 0;
	status->line = NULL;
	status->cpy_stdin = -1;
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
		ex_exit(status, NULL);
	status->exec_count = 0;
	make_env_list(status, env);
	while (1)
	{
		line = readline("\n\n[readline]>> ");
		status->error = 0;
		status->stack = NULL;
		d_printf("[%s]", line);
		check_line(line, status);
		reset_status(status);
		free (line);
	}
	(void)argv;
	(void)env;
	return (0);
}
