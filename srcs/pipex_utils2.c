/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:43:53 by hhino             #+#    #+#             */
/*   Updated: 2023/10/04 17:17:25 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
//	exit_ee(1);
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
