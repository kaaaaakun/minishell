/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:25:09 by tokazaki          #+#    #+#             */
/*   Updated: 2023/08/22 22:32:42 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"

void	wait_process(int pid, int count)
{
	int	i;
	int	status;

	i = 0;
	while (i < count)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) != 0)
			;
		i++;
	}
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) != 0)
		;
}

void	check_command(char *line, int pipe_flag, t_info *status)
{
	ft_putstr_fd("[check_command]", 1);
	char **split;
	extern char **environ;

	split = ft_split(line, ' ');
	if (ft_memcmp(split[0], "exit", 5) == 0)
		ex_exit(split);
	else if (ft_memcmp(split[0], "echo", 5) == 0)
		ex_echo(split);
	else if (ft_memcmp(split[0], "env", 4) == 0)
		ex_env(split);
	else if (ft_memcmp(split[0], "cd", 3) == 0)
		ex_cd(split);
	else if (ft_memcmp(split[0], "pwd", 4) == 0)
		ex_pwd();
	else if (ft_memcmp(split[0], "export", 7) == 0)
		ex_env(split);
	else if (ft_memcmp(line, "<<", 2) == 0)
		ex_env(split);
	else
	{
		usleep(100);
		ft_putendl_fd(ft_strjoin("builtin not found: ", line), 1);
		ex_execve(split, pipe_flag, status);
	}
	if (line)
		add_history(line);
	rl_on_new_line();
	split_free(split);
}

void	check_line(char *line)
{
	ft_putstr_fd("[check_line]", 1);
	int		i;
	int		pipe_flag;;
	char	**splited_pipe;
	t_info	*status;

	status = (t_info *)malloc(sizeof(t_info) * 1);
	if (!status)
		ex_exit(NULL);
	ft_putstr_fd("[check_line]", 1);
	if (!line)
		ex_exit(NULL);
	else if (*line == '\0')
	{
		ft_putstr_fd("", 1);
		rl_on_new_line();
	}
	pipe_flag = 1;
	splited_pipe = ft_split(line, '|');
	i = 0;
	while (splited_pipe[i] != NULL)
	{
		if (splited_pipe[i + 1] == NULL)
			pipe_flag = 0;
		check_command((char *)splited_pipe[i], pipe_flag, status);
		i++;
	}
	if (pipe_flag == 1)
		wait_process(status->pid, i - 1);
	split_free(splited_pipe);
}

void	line_read(void)
{
	char	*line;

	while (1)
	{
		line = readline("[readline]>> ");
		check_line(line);
		free (line);
	}
}

int	main(void)
{
	add_sigaction();
	line_read();
	return (0);
}
