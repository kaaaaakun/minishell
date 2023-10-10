/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_operators.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 18:24:39 by hhino             #+#    #+#             */
/*   Updated: 2023/10/10 19:39:19 by hhino            ###   ########.fr       */
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
	if (g_signal != SIGINT)
		check_infile(status, tmp_file_name);
	(void)status;
	unlink(tmp_file_name);
	free_null(tmp_file_name);
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
	char	*input_line;
	char	*read_line;
	char	*cmd_tmp;
	int		eof_len;
	int		flag;
	int		i;

	ft_printf("read_line : %s", eof_word);
	dup2(status->cpy_stdin, 0);
	// close(status->cpy_stdin);
	eof_len = ft_strlen(eof_word) + 1;
	cmd_tmp = status->line;
	while (1)
	{
		i = 0;
		flag = 0;
		add_sigaction(status, 1);
		read_line = readline(">");
		if (g_signal == SIGINT)
		{
			status->exit_status = 1;
			dup2(status->cpy_stdin, 0);
			break ;
		}
		if (read_line == NULL || ft_strncmp(read_line, eof_word, eof_len) == 0)
		{
			free(read_line);
			break ;
		}
		input_line = check_dollar(status, read_line);
		while (input_line != NULL && input_line[i] != '\0')
		{
			if ((input_line[i] == '\'' || input_line[i] == '\"') && !(flag & IN_QUOTE))
				plusle_quote(input_line[i], &flag);
			else if ((input_line[i] == '\'' && flag & S_QUOTE) || \
				(input_line[i] == '\"' && flag & D_QUOTE))
				minun_quote(input_line[i], &flag);
			else
				ft_putchar_fd(input_line[i], tmp_fd);
			i++;
		}
		ft_putendl_fd("", tmp_fd);
		free(input_line);
		free(read_line);
	}
	status->line = cmd_tmp;
	free_null(eof_word);
	add_sigaction(status, 0);
	close(tmp_fd);
	status->cpy_stdin = dup(0);
}
