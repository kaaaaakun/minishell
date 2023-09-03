/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pino.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 18:48:57 by hhino             #+#    #+#             */
/*   Updated: 2023/09/02 22:02:40 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"

void	init_stack(t_info *status);
void	check_line(char *line, t_info *status);
char	*put_space(char *line);
void	put_to_list(char *str, t_stack *stack);
void	wait_process(t_info *info_status);

void	check_line(char *line, t_info *status)
{
	ft_putstr_fd("[check_line]", 1);
	int		i;
	int		pipe_flag;
	char	**splited_pipe;
	t_stack	*stack;

	i = 0;
	init_stack(status);
	stack = status->stack;
	if (line && *line)
		add_history(line);
	ft_printf("[check_line:%d]", status->exec_count);
	if (!line)
		return (1); //子プロセスをエラーで終了したい
	status->exec_count = 0;
	if (*line == '\0')
		rl_on_new_line();
	pipe_flag = 1;
	splited_pipe = ft_split(line, '|');
	while (splited_pipe[i] != NULL)
	{
		put_to_list(splited_pipe[i], stack);
		stack = stack->next;
		i++;
	}
	wait_process(status);
	split_free(splited_pipe);
}

void	wait_process(t_info *info_status)
{
	int	i;
	int	status;

	ft_printf("[wait;%d]", info_status->exec_count);
	i = 1;
	while (i < info_status->exec_count)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) != 0)
			;
		i++;
	}
	waitpid(info_status->pid, &status, 0);
	if (WEXITSTATUS(status) != 0)
		;
}

//stackの初期化の関数
void	init_stack(t_info *status)
{
	status->stack->outputlist = NULL;
	status->stack->appendlist = NULL;
	status->stack->inputlist = NULL;
	status->stack->heredoclist = NULL;
	status->stack->cmdlist = NULL;
	status->stack->next = NULL;
}

char	*put_space(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '>')
		{
			if (line[i + 1] == '>')
				i++;
			line[i + 1] = ' ';
		}
		else if (line[i] == '<')
		{
			if (line[i + 1] == '<')
				i++;
			line[i + 1] = ' ';
		}
		i++;
	}
	return (line);
}

void	put_to_list(char *line, t_stack *stack)
{
	int		i;
	char	**split_line;
	int		in_fd;
	int		out_fd;

	line = put_space(line);
	split_line = ft_split(line, ' ');
	i = 0;
	while (split_line[i] != NULL)
	{
		if (ft_memcmp(split_line[i], ">", 2))
		{
			in_fd = open(split_line[i + 1], O_RDONLY, 0644);
			if (in_fd == -1)
				return (1); //子プロセスをエラーで終了したい
			i++;
			close(in_fd);
			push_back(&stack->outputlist, split_line[i]);
		}
		else if (ft_memcmp(split_line[i], ">>", 3))
		{
			in_fd = open(split_line[i + 1], O_RDONLY, 0644);
			if (in_fd == -1)
				return (1); //子プロセスをエラーで終了したい
			i++;
			close(in_fd);
			push_back(&stack->appendlist, split_line[i]);
		}
		else if (ft_memcmp(split_line[i], "<", 2))
		{
			out_fd = open(split_line[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);//(か)0777は正確ではないので、変えた方がいいかも
			if (out_fd == -1)
				return (1); //子プロセスをエラーで終了したい
			i++;
			close(out_fd);
			push_back(&stack->inputlist, split_line[i]);
		}
		//else if (ft_memcmp(split_line[i], "<<", 3))
			//??;
		else
		{
			push_back(&stack->cmdlist, split_line[i]);
			ft_printf("\n\n%s\n\n", stack->cmdlist->content);
		}
		i++;
	}
	split_free(split_line);
}

int	main(int argc, char *argv[], char *env[])
{
	char	*line;
	t_info	*status;

	if (argc != 1)
		return (0);
	add_sigaction();
	status = (t_info *)malloc(sizeof(t_info) * 1);
	if (!status)
		return (1);
	status->exec_count = 0;
	status->error = 0;
	make_env_list(status, env);
	while (1)
	{
		line = readline("[readline]>> ");
		ft_printf("[%s]", line);
		check_line(line, status);
		free (line);
	}
	(void)argv;
	(void)env;
	return (0);
}
