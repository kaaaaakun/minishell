/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_operators.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 18:24:39 by hhino             #+#    #+#             */
/*   Updated: 2023/10/13 20:17:54 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_panda.h"
#include "minishell.h"
#include <errno.h>

void	ex_heredoc(t_info *status, char *eof_word, int tmp_fd);

void	check_infile(t_info *status, char *result)
{
	int	fd;

	if (g_signal == SIGINT)
		return ;
	fd = open_ee(status, result, O_RDONLY, 0);
	if (fd < 0)
	{
		status->exit_status = 1;
		return ;
	}
	dup2_ee(status, fd, STDIN_FILENO);
	close_ee(status, fd);
	(void)status;
}

char	*check_heredoc(t_info *status, char *eof_word)
{
	char	*tmp_file_name;
	int		tmp_fd;

	if (g_signal == SIGINT)
		return (NULL);
	tmp_file_name = make_tmp_file(status, &tmp_fd);
	ex_heredoc(status, eof_word, tmp_fd);
	check_infile(status, tmp_file_name);
	(void)status;
	unlink(tmp_file_name);
	free_null(tmp_file_name);
	return (NULL);
}

void	check_outfile(t_info *status, char *result)
{
	int	fd;

	if (g_signal == SIGINT)
		return ;
	fd = open_ee(status, result, O_CREAT | O_TRUNC | O_WRONLY, \
		S_IRWXU | S_IRGRP | S_IROTH);
	if (fd < 0)
	{
		status->exit_status = 1;
		return ;
	}
	dup2_ee(status, fd, STDOUT_FILENO);
	close_ee(status, fd);
	(void)status;
}

void	check_appendfile(t_info *status, char *result)
{
	int	fd;

	if (g_signal == SIGINT)
		return ;
	fd = open_ee(status, result, O_CREAT | O_APPEND | O_WRONLY, \
		S_IRWXU | S_IRGRP | S_IROTH);
	if (fd < 0)
	{
		status->exit_status = 1;
		return ;
	}
	dup2_ee(status, fd, STDOUT_FILENO);
	close_ee(status, fd);
	(void)status;
}
