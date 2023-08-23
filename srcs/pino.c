/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pino.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 18:48:57 by hhino             #+#    #+#             */
/*   Updated: 2023/08/23 20:00:56 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"

void	put_to_list(char *str, t_stack *stack);

void	check_line(char *line, t_info *status)
{
	ft_putstr_fd("[check_line]", 1);
	int		i;
	int		pipe_flag;
	char	**splited_pipe;
	t_stack	*stack;

	i = 0;
	stack = status->stack;
	if (line && *line)
		add_history(line);
	ft_printf("[check_line:%d]", status->exec_count);
	if (!line)
		ex_exit(NULL);
	status->exec_count = 0;
	if (*line == '\0')
		rl_on_new_line();
	pipe_flag = 1;
	splited_pipe = ft_split(line, '|');
	while (splited_pipe[i] != NULL)
	{
		put_to_list(splited_pipe[i], &stack);
		stack = stack->next;
		i++;
	}
	wait_process(status);
	split_free(splited_pipe);
}

void	put_to_list(char *line, t_stack *stack)
{
	int		i;
	char	**split_line;
	int		in_fd;
	int		out_fd;

// もしも<,>,<<,>>の後に' 'がなかったら、' 'を入れる関数を作る？その方が一括でsplitできて楽
	split_line = ft_split(line, ' ');
	i = 0;
	while (split_line[i] != NULL)
	{
		if (ft_memcmp(split_line[i], ">"))
		{
			in_fd = open(split_line[i + 1], O_RDONLY, 0644);
			if (in_fd == -1)
				ex_exit(NULL);
			//push_back

		}
		if (ft_memcmp(split_line[i], ">>"))
		{
			in_fd = open(split_line[i + 1], O_RDONLY, 0644);
			if (in_fd == -1)
				ex_exit(NULL);
			//push_back
		}
		if (ft_memcmp(split_line[i], "<"))
		{
			out_fd = open(split_line[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (out_fd == -1)
				ex_exit(NULL);
			//push_back
		}
		//if (ft_memcmp(split_line[i], "<<"))
			//??;
		else
		{
			//listnewしてpush_backする
			stack->cmdlist->cmd = split_line[i];
		}
		i++;
	}
}
