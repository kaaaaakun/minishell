/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:55:23 by tokazaki          #+#    #+#             */
/*   Updated: 2023/09/14 19:53:19 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"

void	before_pipe(char **command, t_info *status);
void	last_command(char **command, t_info *status);

void	ex_execve(t_info *status)
{
	int	pid;
	int	pipefd[2];

	pipe(pipefd);
	pid = fork();
	if(pid == 0)
	{
		char *cat[] = {"cat", "-n", NULL};
		execve("/bin/cat", cat ,NULL);
		(void)status;
	}
}

void	before_pipe(char **command, t_info *status)
{
	d_printf("[before_pipe:%s]",command[0]);
	char		*path;
	int			pid;
//	int			cpy_stdin = dup(0);
	extern char	**environ;
	int			pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid < 0)
		fork_error_exit("fork");
	if (pid == 0)
	{
		path = check_access(command[0], status);
		if (!path)
			malloc_error();
		dup2_ee(pipefd[1], STDOUT_FILENO);
		close_ee(pipefd[1]);
		close_ee(pipefd[0]);
		execve(path, command, NULL);
	}
	dup2_ee(pipefd[0], STDIN_FILENO);
	close_ee(pipefd[1]);
	status->exec_count++;
	status->pid = pid;
//	dup2(cpy_stdin, 0);
//	close(cpy_stdin);
}

void	last_command(char **command, t_info *status)
{
	d_printf("[las_command:%s]",command[0]);
	char		*path;
	int			pid;
	extern char	**environ;

	pid = fork();
	if (pid < 0)
		fork_error_exit("fork");
	if (pid == 0)
	{
		path = check_access(command[0], status);
		if (!path)
			malloc_error();
		execve(path, command, NULL);
	}
	status->exec_count++;
	status->pid = pid;
}
