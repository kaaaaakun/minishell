/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:25:09 by tokazaki          #+#    #+#             */
/*   Updated: 2023/08/21 13:06:56 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_command(char *line)
{
	char **split;
	extern char **env;

	if (!line)
		ex_exit(NULL);
	split = ft_split(line, ' ');
	if (*line == '\0')
		ft_putstr_fd("", 1);
	else if (ft_memcmp(split[0], "exit", 5) == 0)
		ex_exit(split);
	else if (ft_memcmp(split[0], "echo", 5) == 0)
		ex_echo(split);
	else if (ft_memcmp(line, "env", 4) == 0)
		ex_env(split);
	else if (ft_memcmp(line, "cd", 3) == 0)
		ex_env(split);
	else if (ft_memcmp(line, "pwd", 4) == 0)
		ex_env(split);
	else if (ft_memcmp(line, "unlink", 7) == 0)
		ex_env(split);
	else if (ft_memcmp(line, "export", 7) == 0)
		ex_env(split);
	else if (ft_memcmp(line, "<<", 2) == 0)
		ex_env(split);
	else
		ft_putendl_fd(ft_strjoin("builtin not found: ", line), 1);
	if (line)
		add_history(line);
	rl_on_new_line();
}

void	check_line(char *line)
{
	int		i;
	char	**split;

	split = ft_split(line, '|');
	i = 0;
	while (split[i] != NULL)
	{
//ft_printf ("[%d]",i);
		check_command((char *)split[i]);
//		check_doc(split[i], env);
		i++;
	}
}

void	line_read(void)
{
	char	*line;

	while (1)
	{
		line = readline(">> ");
		if (!line)
			ex_exit(0);
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
