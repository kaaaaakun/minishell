/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:17:45 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/06 17:22:04 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_ee(t_info *status, int nbr)
{
	status->exit_status = nbr;
	status->error = nbr;
}

int	open_ee(t_info *status, char *str, int oflag, int orflag)
{
	int	fd;

	fd = open(str, oflag, orflag);
	if (fd < 0)
	{
		perror(str);
		exit_ee (status, 1);
	}
	return (fd);
}

void	dup2_ee(t_info *status, int fd, int std)
{
	int	flag;

	flag = dup2(fd, std);
	if (flag < 0)
	{
		perror("dup2");
		exit_ee (status, 1);
	}
}

void	close_ee(t_info *status, int fd)
{
	int	flag;

	flag = close(fd);
	if (flag < 0)
	{
		perror("close");
		exit_ee (status, 1);
	}
}
