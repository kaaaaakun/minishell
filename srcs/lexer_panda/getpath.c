/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 19:56:26 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/09 15:26:11 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"
#include "lexer_panda.h"

char	**getpath(t_info *status)
{
	char	**path;
	char	*long_path;

	long_path = search_env(status, "PATH");
	path = ft_split(long_path, ':');
	if (!path)
		return (NULL);
	return (path);
}

void	*command_and_split_free(char *command, char **path)
{
	free(command);
	split_free(path);
	return (NULL);
}

char	*check_path(char *command, char **path)
{
	int		i;
	char	*collect_path;

	i = 0;
	if (!command || !path)
		return (NULL);
	while (path[i] != NULL)
	{
		collect_path = ft_strjoin_free(path[i], command, NEITHER_FREE);
		if (collect_path == NULL)
			return (command_and_split_free(command, path));
		if (access(collect_path, F_OK) == 0)
		{
			command_and_split_free(command, path);
			return (collect_path);
		}
		free_null(collect_path);
		i++;
	}
	return (command_and_split_free(command, path));
}

int	access_ee(char *command, int flag, int free_flag)
{
	int	result;

	result = access(command, flag);
	if (free_flag != 0)
		free_null(command);
	return (result);
}

char	*check_access(char *command, t_info *status)
{
	if (!command)
		return (NULL);
	if (access_ee(ft_strtrim_free(command, "./", NEITHER_FREE), \
				F_OK, FIRST_FREE) == 0)
		return (ft_strtrim_free(command, "./", NEITHER_FREE));
	else if (access(command, F_OK) == 0)
		return (command);
	return (check_path(ft_strjoin_free("/", command, NEITHER_FREE), \
				getpath(status)));
}
