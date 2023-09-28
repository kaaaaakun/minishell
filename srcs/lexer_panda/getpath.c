/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 19:56:26 by tokazaki          #+#    #+#             */
/*   Updated: 2023/09/28 20:27:02 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"
#include "lexer_panda.h"

void	malloc_error(void)
{
	perror("malloc");
	exit (1);
}

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

char	*check_path(char *command, char **path)
{
	int		i;

	i = 0;
	if (!command || !path)
		return (NULL);
	while (path[i] != NULL)
	{
		path[i] = ft_strjoin_free(path[i], command, NEITHER_FREE);
		if (path[i] == NULL)
		{
			free(command);
			split_free(path);
			return (NULL);
		}
		if (access(path[i], X_OK) == 0)
		{
			free(command);
			char *collect_path = ft_strdup(path[i]);
			split_free(path);
			return (collect_path);
		}
		i++;
	}
	free(command);
	split_free(path);
	return (NULL);
}

char	*check_access(char *command, t_info *status)
{
	if (!command)
		return (NULL);
	if (access(ft_strtrim(command, "./"), X_OK) == 0)
		return (ft_strtrim(command, "./"));
	else if (access(command, X_OK) == 0)
		return (command);
	return (check_path(ft_strjoin_free("/", command, NEITHER_FREE), getpath(status)));
}
