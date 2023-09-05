/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:28:35 by tokazaki          #+#    #+#             */
/*   Updated: 2023/09/05 20:13:06 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexar_panda.h"
#include "pipex.h"
void	check_infile(t_info *status, char *result)
{
	int fd;

	fd = open_ee(result, O_RDONLY, 0);
	dup2_ee(fd, STDIN_FILENO);
	close_ee(fd);
	(void)status;
}

void	check_outfile(t_info *status, char *result)
{
	int fd;

	fd = open_ee(result, O_CREAT | O_TRUNC | O_WRONLY, \
		S_IRWXU | S_IRGRP| S_IROTH);
	dup2_ee(fd, STDOUT_FILENO);
	close_ee(fd);
	(void)status;
}

void	check_command_path(t_info *status, char *result)
{
	char	*path;
	char	**splited_path;

	path = serch_env(status, "PATH");
	splited_path = ft_split(path, ':');
	path = check_path(result, splited_path);
	(void)result;
	(void)status;
}

void	check_flag(t_info *status, char *result, int *flag)
{
	return ;//ここで一回止めてる
	if (*flag & INPUT_REDIRECT)
		check_infile(status, result);
	else if (*flag & OUTPUT_REDIRECT)
		check_outfile(status, result);
	else if (!(*flag & COMMAND))
		check_command_path(status, result);
}

char	*make_list(int *flag, char *line, int len, t_list **list)
{
	char	*result;

	result = ft_substr(line, 0, len);
	if (!result)
	{
//		status->error == 1;
		return (NULL);
	}
	push_back(list, result);
	return (result);
	(void)flag;
}
