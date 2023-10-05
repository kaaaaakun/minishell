/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:25:09 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/04 18:04:52 by hhino            ###   ########.fr       */
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
	int			cpy_stdout;

	status->cpy_stdin = dup(0);//標準入出力の管理
	cpy_stdout = dup(1);
	panda(status->line, status);//メインの処理
	debug(status,"panda to check");
	if (status->pipe == 0 && status->error == 0)//pipeがない（forkがなかった場合）
	{
		check_command(status, status->stack);
		free_stack(status);
	}
	dup2(status->cpy_stdin, 0);
	dup2(cpy_stdout, 1);
}

void	pre_line_check(t_info *status)
{
	d_printf("[check_line]", 1);
	char *line;

	line = status->line;
	if (line && *line)
		add_history(line);
	if (!line)
		ex_exit(status, NULL);//EOFの入力で終了
	if (*line == '\0')//何も入力されてなければreadlineに戻る
	{
		rl_on_new_line();
		return ;
	}
	execute_main_process(status);//ここからがメインの処理
}

int	main(int argc, char *argv[], char *env[])
{
	t_info	*status;

	if (argc != 1)
	{
		printf("minishell: %s: No such file or directory\n", argv[1]);
		return (0);
	}
	status = (t_info *)ft_calloc(sizeof(t_info), 1);
	if (!status)
		exit(1);
	make_env_list(status, env);
	while (1)
	{
		add_sigaction(0);
		status->line = readline("minishell$ ");
		d_printf("[%s]", status->line);
		pre_line_check(status);
		reset_status(status);
		if (g_signal == SIGINT)
			status->exit_status = 130;
	}
	(void)argv;
	(void)env;
	return (0);
}
