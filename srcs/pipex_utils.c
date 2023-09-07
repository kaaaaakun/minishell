/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:17:45 by tokazaki          #+#    #+#             */
/*   Updated: 2023/09/07 16:11:41 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_ee(int nbr)
{
	int	fork_id;

	fork_id = fork();
	if (fork_id == 0)
		exit (nbr);
}

void	split_free(char **result)
{
	int	i;

	i = 0;
	while (result[i] != NULL)
	{
		free(result[i]);
		i++;
	}
	free(result);
}

void	error_exit(char *msg)
{
	perror(msg);
	exit_ee(1);
}

void	fork_error_exit(char *msg)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		error_exit("fork");
	if (pid == 0)
	{
		perror(msg);
		exit(1);
	}
}

int	open_ee(char *str, int oflag, int orflag)
{
	int	fd;

	fd = open(str, oflag, orflag);
	if (fd < 0)
	{
		perror(str);
		exit_ee(1);
	}
	return (fd);
}

void	dup2_ee(int fd, int std)
{
	int	flag;

	flag = dup2(fd, std);
	if (flag < 0)
	{
		perror("dup2");
		exit_ee (1);
	}
}

void	close_ee(int fd)
{
	int	flag;

	flag = close(fd);
	if (flag < 0)
	{
		perror("close");
		exit_ee (1);
	}
}
