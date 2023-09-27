/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:55:23 by tokazaki          #+#    #+#             */
/*   Updated: 2023/09/27 14:33:20 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"
#include "typedef_struct.h"

void	before_pipe(char **command, t_info *status);
void	last_command(char **command, t_info *status);
char	*check_access(char *command, t_info *status);

char	**generate_cmdstr(t_info *status)
{
	char	**cmdstr;
	t_list	*list;
	int		i;

	i = 0;
	list = status->stack->cmdlist;
	cmdstr = (char **)malloc(sizeof(char *) * (listsize(list) + 1));
	while (list != NULL)
	{
		cmdstr[i] = ft_strdup(list->content);
		list = list->next;
		i++;
	}
	cmdstr[i] = NULL;
	return (cmdstr);
}

void	ex_execve(t_info *status)
{
	int		pid;
	char	*path;
	char	**cmd;

	cmd = generate_cmdstr(status);
	path = check_access(status->stack->cmdlist->content, status);
	if (status->pipe == 0)
	{
		pid = fork();
		if (pid == 0)
			execve(path, cmd, NULL);
		waitpid(pid, NULL, 0);
	}
	else
	{
		d_printf("AAAAAAAAAAAAAA\n");
		execve(path, cmd, NULL);
	}
	(void)pid;
}


// void	ex_execve(t_info *status)
// {
// 	int	pid;
// 	int	pipefd[2];

// 	pipe(pipefd);
// 	pid = fork();
// 	if(pid == 0)
// 	{
// 		dup2_ee(pipefd[0], STDIN_FILENO);
// 		close_ee(pipefd[0]);
// 		close_ee(pipefd[1]);
// 		char *cat[] = {"cat", "-n", NULL};
// 		execve("/bin/cat", cat ,NULL);
// 		(void)status;
// 	}
// 	dup2_ee(pipefd[1], STDOUT_FILENO);
// 	close_ee(pipefd[0]);
// }

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

// void	last_command(char **command, t_info *status)
// {
// 	d_printf("[las_command:%s]",command[0]);
// 	char		*path;
// 	int			pid;
// 	extern char	**environ;

// 	if (status->pipe == 0)
// 	{
// 		pid = fork();
// 		if (pid < 0)
// 			fork_error_exit("fork");
// 		if (pid == 0)
// 		{
// 			path = check_access(command[0], status);
// 			if (!path)
// 				malloc_error();
// 			execve(path, command, NULL);
// 		}
// 	}
// 	else
// 		execve(path, command, NULL);
// 	status->exec_count++;
// 	status->pid = pid;
// }
