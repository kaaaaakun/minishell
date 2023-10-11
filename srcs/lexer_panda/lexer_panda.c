/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_panda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 17:48:21 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/11 17:45:59 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_panda.h"
#include "builtin.h"

void	exec_panda(char *line, t_info *status, int flag)
{
	int	i;
	int	j;
	int	value;

	while (*line != '\0')
	{
		i = 0;
		value = analysis_char(*line);
		if (value == 1 || value == 0)
		{
			j = process_quotes(line, &value, &i, &flag);
			process_input_operation(status, line, j, &flag);
		}
		if (value == 2)
			i++;
		else if (value == 3 && !(flag & IN_QUOTE))
			i += process_input_redirect_operation(status, line, &flag);
		else if (value == 4 && !(flag & IN_QUOTE))
			i += process_output_redirect_operation(status, line, &flag);
		else if (value == 6 && !(flag & IN_QUOTE))
			return ;
		line += i;
		if (status->error != 0)
			return ;
	}
}

void	wait_child_process(t_info *status, pid_t pid)
{
	int	process_count;
	int	i;
	int	exit_status;
	int	flag;

	flag = 0;
	process_count = status->pipe + 1;
	i = 0;
	while (i < process_count)
	{
		if (waitpid(-1, &exit_status, 0) == pid)
		{
			flag = 1;
			if (WIFEXITED(exit_status))
				status->exit_status = WEXITSTATUS(exit_status);
			else if (WIFSIGNALED(exit_status))
				status->exit_status = WTERMSIG(exit_status) + 128;
		}
		i++;
	}
	if (flag == 1)
		g_signal = 0;
}

void	some_pipes_exec_panda(t_info *status, char *line, int flag, int i)
{
	int		stdin_fd;
	pid_t	pid;
	int		pipefd[2];

	stdin_fd = dup(STDIN_FILENO);
	while (++i)
	{
		if (pipe(pipefd) < 0)
			error_exit("pipe");
		pid = fork_ee();
		if (pid == 0)
		{
			if (i != status->pipe + 1)
				dup2_close_pipe(status, pipefd, STDOUT_FILENO);
			exec_panda(line, status, flag);
			add_sigaction(status, 2);
			check_command(status, status->stack);
		}
		line = mini_ft_strchr(line, '|');
		if (line == NULL)
			break ;
		line++;
		dup2_close_pipe(status, pipefd, STDIN_FILENO);
	}
	dup2_ee(status, stdin_fd, STDIN_FILENO);
	add_sigaction(status, 3);
	wait_child_process(status, pid);
}

void	panda(char *line, t_info *status)
{
	int		flag;
	int		i;

	d_printf("[panda]");
	i = 0;
	if (*line == '\0')
		return ;
	line = check_dollar(status, line);
	d_printf("[panda : line %s]", line);
	check_error(status, line, &flag);
	if (flag & ERROR)
	{
		lexer_panda_error_check(&flag, status);
		d_printf("syntax error \n");
		status->error = -1;
		free_null(line);
		return ;
	}
	make_stack(status, NULL);
	status->pipe = check_and_count_pipe(status, line);
	if (status->pipe == 0)
		exec_panda(line, status, flag);
	else
		some_pipes_exec_panda(status, line, flag, i);
	free(line);
	return ;
}
