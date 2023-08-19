/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:25:09 by tokazaki          #+#    #+#             */
/*   Updated: 2023/08/19 17:44:10 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

void	check_command(char *line, char **env)
{
	char **split;

	split = ft_split(line, ' ');
	if (!line)
		ex_exit(NULL);
	else if (*line == '\0')
		ft_putstr_fd("", 1);
	else if (ft_memcmp(split[0], "exit", 5) == 0)
		ex_exit(split);
	else if (ft_memcmp(split[0], "echo", 5) == 0)
		ex_echo(split);
	else if (ft_memcmp(line, "env", 4) == 0)
		ex_env(split, env);
	else if (ft_memcmp(line, "cd", 3) == 0)
		ex_env(split, env);
	else if (ft_memcmp(line, "pwd", 4) == 0)
		ex_env(split, env);
	else if (ft_memcmp(line, "unlink", 7) == 0)
		ex_env(split, env);
	else if (ft_memcmp(line, "export", 7) == 0)
		ex_env(split, env);
	else if (ft_memcmp(line, "<<", 2) == 0)
		ex_env(split, env);
	else
		ft_putstr_fd(ft_strjoin("builtin not found: ", line), 1);
}

void	check_line(char *line, char **env)
{
	check_command(line, env);
//	int	i;
//
//	i = 0;
//	while (split[i] != NULL)
//	{
//		check_command(split[i], env);
//		check_doc(split[i], env);
//		i++;
//	}
}

int	main(int argc, char *argv[], char **env)
{
	//char	*line = NULL;
	char	*line;
	int		i;

	i = 0;
	(void)argc;
	(void)argv;
	while (1)
	{
		ft_printf("my-shell[%d]:",i);
		line = get_next_line(0);
		//readline(line);
		check_line(ft_strtrim(line, "\n"), env);
		free (line);
		i++;
	}
	return (0);
}
