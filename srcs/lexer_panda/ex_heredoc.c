/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 20:15:23 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/13 20:15:49 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_panda.h"
#include "minishell.h"
#include <errno.h>

void	putchar_to_tmpfile(char *input_line, int tmp_fd)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (input_line != NULL && input_line[i] != '\0')
	{
		if ((input_line[i] == '\'' || input_line[i] == '\"') && \
			!(flag & IN_QUOTE))
			plusle_quote(input_line[i], &flag);
		else if ((input_line[i] == '\'' && flag & S_QUOTE) || \
			(input_line[i] == '\"' && flag & D_QUOTE))
			minun_quote(input_line[i], &flag);
		else
			ft_putchar_fd(input_line[i], tmp_fd);
		i++;
	}
	ft_putendl_fd("", tmp_fd);
}

void	heredoc_readline(t_info *status, int tmp_fd, char *eof_word)
{
	char	*input_line;
	char	*read_line;

	while (1)
	{
		add_sigaction(status, 1);
		read_line = readline(">");
		if (g_signal == SIGINT)
		{
			status->exit_status = 1;
			dup2(status->cpy_stdin, 0);
			break ;
		}
		if (read_line == NULL || ft_strncmp(read_line, eof_word, \
			ft_strlen(eof_word) + 1) == 0)
		{
			d_printf("[%s,%p]", eof_word, eof_word);
			free(read_line);
			break ;
		}
		input_line = check_dollar(status, read_line);
		putchar_to_tmpfile(input_line, tmp_fd);
		free(input_line);
		free(read_line);
	}
}

void	ex_heredoc(t_info *status, char *eof_word, int tmp_fd)
{
	char	*line;

	d_printf("read_line : %s : %d", eof_word, g_signal);
	line = status->line;
	if (g_signal == SIGINT)
		return ;
	dup2(status->cpy_stdin, 0);
	heredoc_readline(status, tmp_fd, eof_word);
	free_null(eof_word);
	add_sigaction(status, 0);
	close(tmp_fd);
	status->line = line;
	status->cpy_stdin = dup(0);
}
