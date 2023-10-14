/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_panda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 17:48:21 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/13 15:33:04 by tokazaki         ###   ########.fr       */
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
	int	exit_status;
	int	flag;

	flag = 0;
	process_count = status->pipe + 1;
	add_sigaction(status, 4);
	while (process_count--)
	{
		if (pid < 0)
		{
			status->exit_status = 1;
			break ;
		}
		if (waitpid(-1, &exit_status, 0) == pid)
		{
			flag = 1;
			if (WIFEXITED(exit_status))
				status->exit_status = WEXITSTATUS(exit_status);
			else if (WIFSIGNALED(exit_status))
				status->exit_status = WTERMSIG(exit_status) + 128;
		}
	}
	if (flag == 1)
		g_signal = 0;
}

void	exec_child_process(int process_count, t_info *status, \
			char *line, int *pipefd)
{
	int	flag;

	flag = 0;
	if (process_count != 0)
		dup2_close_pipe(status, pipefd, STDOUT_FILENO);
	exec_panda(line, status, flag);
	if (status->stack->cmdlist == NULL)
		exit(0);
	add_sigaction(status, 2);
	check_command(status, status->stack);
	(void)process_count;
}

void	some_pipes_exec_panda(t_info *status, char *line, int process_count)
{
	int		stdin_fd;
	pid_t	pid;
	int		pipefd[2];

	stdin_fd = dup(STDIN_FILENO);
	while (process_count--)
	{
		if (pipe(pipefd) < 0)
			error_exit("pipe");
		pid = fork_ee(status);
		if (pid < 0)
			break ;
		if (pid == 0)
			exec_child_process(process_count, status, line, pipefd);
		line = mini_ft_strchr(line, '|');
		if (line == NULL)
			break ;
		line++;
		dup2_close_pipe(status, pipefd, STDIN_FILENO);
		d_printf("[pipefd:%d]", pipefd[0]);
	}
	dup2_ee(status, stdin_fd, STDIN_FILENO);
	close_pipe(status, pipefd);
	close (stdin_fd);
	wait_child_process(status, pid);
}

void	panda(char *line, t_info *status)
{
	int		flag;

	d_printf("[panda]");
	if (*line == '\0')
		return ;
	line = check_dollar(status, line);
	check_error(status, line, &flag);
	if (flag & ERROR || flag & AT_PIPE)
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
		some_pipes_exec_panda(status, line, status->pipe + 1);
	free(line);
	return ;
}
