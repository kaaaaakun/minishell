/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:25:09 by tokazaki          #+#    #+#             */
/*   Updated: 2023/08/26 21:14:32 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"

void print_data(void *data) {
    ft_printf("%s\n", (char *)data);
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

void	check_command(char *line, int pipe_flag, t_info *status)
{
	ft_putstr_fd("[check_command]", 1);
	char		 **split;
	extern char	**environ;

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
	else
	{
		usleep(100);
		ft_putendl_fd(ft_strjoin("builtin not found: ", line), 1);
		ex_execve(split, pipe_flag, status);
	}
	rl_on_new_line();
	split_free(split);
}

void	check_line(char *line, t_info *status)
{
	ft_putstr_fd("[check_line]", 1);
//	int		i;
	int		pipe_flag;;
//	char	**splited_pipe;

	if (line && *line)
		add_history(line);
	ft_printf("[check_line:%d]", status->exec_count);
	if (!line)
		ex_exit(NULL);
//	if (!line )//&& status->exec_count != 0)
//	{
//		ft_printf("[check_line:%d/%s]", status->exec_count, line);
//		status->exec_count = 0;
//		ft_putendl_fd("", 1);
//		rl_on_new_line();
//		sleep(10);
//		return ;
//	}
	status->exec_count = 0;
	if (*line == '\0')
	{
		ft_putstr_fd("", 1);
		rl_on_new_line();
	}
	pipe_flag = 1;
//	splited_pipe = ft_split(line, '|');
//	i = 0;
	lekpan(line, status);
//	ft_lstiter(status->env, print_data); listの中身を全て表示するやるやつ
//	while (splited_pipe[i] != NULL)
//	{
//		ft_printf("[pipe:%d]\n",i);
//		if (splited_pipe[i + 1] == NULL)
//			pipe_flag = 0;
//		i++;
//	}
	wait_process(status);
//	split_free(splited_pipe);
	(void)pipe_flag;
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
		ex_exit(NULL);
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
