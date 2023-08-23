/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:25:09 by tokazaki          #+#    #+#             */
/*   Updated: 2023/08/23 18:47:22 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"

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
	else if (ft_memcmp(line, "<<", 2) == 0)
		ex_heredoc(line);
	else
	{
		usleep(100);
		ft_putendl_fd(ft_strjoin("builtin not found: ", line), 1);
		ex_execve(split, pipe_flag, status);
	}
	rl_on_new_line();
	split_free(split);
}

int	analysis_char(char c)
{
	if (ft_isdigit(c) || ft_isalpha(c) || c =='-' || c =='_')
		return (1);
	if (c == ' ')
		return (2);
	if (c == '<')
		return (3);
	if (c == '>')
		return (4);
	if (c == '$')
		return (5);
	if (c == '|')
		return (6);
	if (c == '\"')
		return (7);
	if (c == '\'')
		return (8);
	if (c == ';')
		return (10);
	return(0);
}

void	lekpan(char *line, t_info *status)
{
	int	quote_f;
	int	i;
	int	value;
	int	flag;
	int	heredoc;

	quote_f = 0;
	flag = 0;
	heredoc = 0;
	while(*line != '\0')
	{
		i = 0;
		value = -1;
		value = analysis_char(*line);
		if (quote_f == 1)// in quote
		{
			while (line[i] != '\"' )//&& line[i] != '\0')
			{
				ft_printf("%c", line[i]);
				i++;
			}
			ft_printf(" |command\n");
			i++;
			quote_f = 0;
		}
		else if (value == 1)// noflags
		{
			while (analysis_char(line[i]) == value)
			{
				ft_printf("%c", line[i]);
				i++;
			}
				if (flag == 0)
					ft_putendl_fd(" | command", 1);
				else if (heredoc == 1)
				{
					heredoc = 0;
					ft_putendl_fd(" | heredoc EOF", 1);
				}
				else
					ft_putendl_fd(" | file", 1);
			flag = 0;
		}
		else if (value == 2)// ' '
		{
			while (analysis_char(line[i]) == value)
			{
				i++;
			}
		}
		else if (value == 3)// < << <<<
		{
			while (analysis_char(line[i]) == value)
			{
				ft_printf("%c", line[i]);
				i++;
			}
			if (2 < i || flag)
				ft_putendl_fd(" | syntax error near unexpected token `<'", 1);
			else if (i == 2)
			{
				ft_putendl_fd(" | heredoc", 1);	
				flag = 1;
				heredoc = 1;
			}
			else if (i == 1)
			{
				ft_putendl_fd(" | redirect", 1);
				flag = 1;
			}
		}
		else if (value == 4)// > >> >>>
		{
			while (analysis_char(line[i]) == value)
			{
				ft_printf("%c", line[i]);
				i++;
			}
			if (2 < i || flag)
				ft_putendl_fd(" | syntax error near unexpected token `>'", 1);
			else if (i == 2)
			{
				ft_putendl_fd(" | re:heredoc", 1);	
				flag = 1;
			}
			else if (i == 1)
			{
				ft_putendl_fd(" | re:redirect", 1);
				flag = 1;
			}
		}
		else if (value == 6)// |
		{
			while (analysis_char(line[i]) == value)
			{
				ft_printf("%c", line[i]);
				i++;
			}
			if (1 < i)
				ft_putendl_fd(" | syntax error near unexpected token `|'", 1);
			else if (i == 1)
			{
				ft_putendl_fd(" | pipe", 1);
				flag = 1;
			}
		}
		else if (value == 7)// "
		{
			quote_f = 1;
			i++;
		}
		else
		{
			ft_printf("%c | else\n", *line);
			line++;
		}
		line += i;
	}
	(void)status;
	(void)i;
}

void	check_line(char *line, t_info *status)
{
	ft_putstr_fd("[check_line]", 1);
	int		i;
	int		pipe_flag;;
	char	**splited_pipe;

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
	splited_pipe = ft_split(line, '|');
	i = 0;
	lekpan(line, status);
	while (splited_pipe[i] != NULL)
	{
		ft_printf("[pipe:%d]\n",i);
		if (splited_pipe[i + 1] == NULL)
			pipe_flag = 0;
	//lekpan(splited_pipe[i], status);
//		check_command((char *)splited_pipe[i], pipe_flag, status);
		i++;
	}
	wait_process(status);
	split_free(splited_pipe);
	(void)pipe_flag;
}

void	line_read(void)
{
	char	*line;
	t_info	*status;

	status = (t_info *)malloc(sizeof(t_info) * 1);
	if (!status)
		ex_exit(NULL);
	status->exec_count = 0;
	while (1)
	{
		line = readline("[readline]>> ");
		ft_printf("[%s]", line);
		check_line(line, status);
		free (line);
	}
}

int	main(void)
{
//	add_sigaction();
	line_read();
	return (0);
}
