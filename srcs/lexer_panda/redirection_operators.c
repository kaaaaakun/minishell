/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_operators.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 18:24:39 by hhino             #+#    #+#             */
/*   Updated: 2023/10/03 20:11:07 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_panda.h"
#include "minishell.h"
#include <errno.h>

void	check_infile(t_info *status, char *result)
{
	int	fd;

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

	tmp_file_name = make_tmp_file(status, &tmp_fd);
	ex_heredoc(status, eof_word, tmp_fd);
	check_infile(status, tmp_file_name);
	(void)status;
	unlink(tmp_file_name);
	return (NULL);
}

void	check_outfile(t_info *status, char *result)
{
	int	fd;

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

void	ex_heredoc(t_info *status, char *eof_word, int tmp_fd)
{
	char	*line;
	int		eof_len;
	int		cpy_stdin;

	dup2(status->cpy_stdin, 0);
	cpy_stdin = dup(0);
	close(status->cpy_stdin);
	status->cpy_stdin = cpy_stdin;
	eof_len = ft_strlen(eof_word) + 1;
	while (1)
	{
		add_sigaction(1);
		// if (g_signal == SIGINT)
		// 	status->exit_status = 1;
		line = readline(">");
		if (ft_strncmp(line, eof_word, eof_len) == 0)
		{
			free(line);
			break ;
		}
		if (line == NULL)
			break ;
		ft_putendl_fd(line, tmp_fd);
		free(line);
	}
	add_sigaction(0);
	close(tmp_fd);
	(void)status;
}
