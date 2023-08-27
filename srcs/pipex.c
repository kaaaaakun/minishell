/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 13:09:27 by tokazaki          #+#    #+#             */
/*   Updated: 2023/08/27 19:15:39 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex(int argc, char *argv[], char *env[])
{
	pid_t	pid;
	int		pipefd[2];

	if (argc != 5)
	{
		ft_putendl_fd("Please enter correct value", 2);
		return (0);
	}
	if (pipe(pipefd) < 0)
		error_exit("pipe");
	pid = fork();
	if (pid < 0)
		error_exit("fork");
	if (pid == 0)
		firstfork(argv, pipefd, env);
	dup2_ee(pipefd[0], STDIN_FILENO);
	close_ee(pipefd[1]);
	pid = fork();
	if (pid < 0)
		error_exit("fork");
	if (pid == 0)
		lastfork(argv, pipefd, env);
	waitchild(pid);
}

void	firstfork(char **argv, int *pipefd, char **env)
{
	int		fd;
	char	*path;
	char	**command;

	fd = open_ee(argv[1], O_RDONLY, 0);
	dup2_ee(fd, STDIN_FILENO);
	close_ee(fd);
	fd = pipefd[1];
	dup2_ee(fd, STDOUT_FILENO);
	close_ee(fd);
	close_ee(pipefd[0]);
	command = ft_split(argv[2], ' ');
	if (!command)
		malloc_error();
	path = check_access(command[0], env);
	if (!path)
		malloc_error();
	execve(path, command, NULL);
}

void	lastfork(char **argv, int *pipefd, char **env)
{
	int		fd;
	char	*path;
	char	**command;

	(void)pipefd;
	fd = open_ee(argv[4], O_CREAT | O_TRUNC | O_WRONLY, \
		S_IRWXU | S_IRWXG | S_IRWXO);
	dup2_ee(fd, STDOUT_FILENO);
	close_ee(fd);
	command = ft_split(argv[3], ' ');
	if (!command)
		malloc_error();
	path = check_access(command[0], env);
	if (!path)
		malloc_error();
	execve(path, command, NULL);
}

void	waitchild(int pid)
{
	int	i;
	int	status;

	i = 0;
	while (i < 1)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) != 0)
			exit(1);
		i++;
	}
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) != 0)
		exit(1);
	exit(0);
}
