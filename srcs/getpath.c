/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 19:56:26 by tokazaki          #+#    #+#             */
/*   Updated: 2023/08/15 16:35:29 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	malloc_error(void)
{
	perror("malloc");
	exit (1);
}

char	**getpath(char **env)
{
	char	**path;
	int		i;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	path = ft_split(&env[i][5], ':');
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
		path[i] = ft_strjoin(path[i], command);
		if (path[i] == NULL)
			return (NULL);
		if (access(path[i], X_OK) == 0)
			return (path[i]);
		i++;
	}
	split_free(path);
	ft_putstr_fd("command not found: ", STDERR_FILENO);
	ft_putendl_fd(ft_strtrim(command, "/"), STDERR_FILENO);
	exit (1);
}

char	*check_access(char *command, char **env)
{
	if (!command)
		return (NULL);
	if (access(ft_strtrim(command, "./"), X_OK) == 0)
		return (ft_strtrim(command, "./"));
	else if (access(command, X_OK) == 0)
		return (command);
	return (check_path(ft_strjoin("/", command), getpath(env)));
}
