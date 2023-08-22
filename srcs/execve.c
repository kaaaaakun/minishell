/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:55:23 by tokazaki          #+#    #+#             */
/*   Updated: 2023/08/22 17:51:02 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"

void	ex_execve(char **command, int pipe_flag, t_info *status)
{
	ft_printf("[execve:%s]",command[0]);
	char		*path;
	int			pid;
	extern char	**environ;
	int			pipefd[2];

	if (pipe_flag == 1)
		pipe(pipefd);
	pid = fork();
	ft_printf("[%d]",pid);
	if (pid < 0)
		fork_error_exit("fork");
	if (pid == 0)
	{
		path = check_access(command[0], environ);
		if (!path)
			malloc_error();
		if (pipe_flag == 1)
		{
			dup2_ee(pipefd[1], STDOUT_FILENO);
			close_ee(pipefd[1]);
			close_ee(pipefd[0]);
		}
		execve(path, command, NULL);
	}
	if (pipe_flag == 1)
	{
		dup2_ee(pipefd[0], STDIN_FILENO);
		close_ee(pipefd[1]);
	}
	status->pid = pid;
}
