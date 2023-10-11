/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:25:09 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/10 20:36:23 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"
#include "builtin.h"

int	g_signal = 0;

void	check_command(t_info *status, t_stack *data);
void	check_line(char *line, t_info *status);

void	reset_status(t_info *status);

void	reset_status(t_info *status)
{
	status->pid = 0;
	status->pipe = 0;
	status->error = 0;
	free_null(status->line);
	free_stack(status);
	status->stack = NULL;
	status->cpy_stdin = -1;
}

void	execute_main_process(t_info *status)
{
	d_printf("[execute_main_process]");
	status->cpy_stdin = dup(0);
	status->cpy_stdout = dup(1);
	panda(status->line, status);
	if (status->pipe == 0 && status->error == 0)
	{
		check_command(status, status->stack);
		// free_stack(status);
	}
	dup2(status->cpy_stdin, 0);
	close (status->cpy_stdin);
	dup2(status->cpy_stdout, 1);
	close (status->cpy_stdout);
	d_printf("[execute_main_process]");
}

void	pre_line_check(t_info *status)
{
	char	*line;
	int		i;

	i = 0;
	d_printf("[check_line]", 1);
	line = status->line;
	if (!line)
		ex_exit(status, NULL);
	while (isspace(line[i]) != 0)
		i++;
	if (line[i] == '\0')
	{
		rl_on_new_line();
		return ;
	}
	else
		add_history(line);
	execute_main_process(status);
	d_printf("[post_check_line]", 1);
}

int	main(int argc, char *argv[], char *env[])
{
	t_info	*status;

	if (argc != 1)
	{
		ft_printf("minishell: %s: No such file or directory\n", argv[1]);
		return (127);
	}
	status = (t_info *)ft_calloc(sizeof(t_info), 1);
	if (!status)
		exit(1);
	status->exit_status = 0;
	make_env_list(status, env);
	while (1)
	{
		g_signal = 0;
		add_sigaction(status, 0);
		status->line = readline("minishell$ ");
		d_printf("[%s]", status->line);
		pre_line_check(status);
		if (g_signal == SIGINT)
		{
			status->exit_status = 1;
		}
		d_printf("[post_main]");
		reset_status(status);
	}
	(void)argv;
	(void)env;
	return (0);
}
