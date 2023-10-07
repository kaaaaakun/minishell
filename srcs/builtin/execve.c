/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:55:23 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/07 21:11:50 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"
#include "builtin.h"
#include "typedef_struct.h"
#include <errno.h>

void	is_no_file_error(t_info *status);
void	is_directory_error(t_info *status, char *path);
void	is_non_xok(t_info *status);

void	erro_msg_no_such_file(t_info *status, char *content);
void	erro_msg_is_a_directory(t_info *status, char *content);
void	erro_msg_permission_denied(t_info *status, char *content);
void	erro_msg_not_command_found(t_info *status, char *content);
char	*check_access(char *command, t_info *status);

char	**generate_cmdstr(t_info *status)
{
	char	**cmdstr;
	t_list	*list;
	int		i;

	i = 0;
	list = status->stack->cmdlist;
	cmdstr = (char **)malloc(sizeof(char *) * (listsize(list) + 1));
	while (list != NULL)
	{
		cmdstr[i] = ft_strdup(list->content);
		list = list->next;
		i++;
	}
	cmdstr[i] = NULL;
	return (cmdstr);
}

char	**env_list(t_info *status)
{
	char	**result;
	t_list	*tmp_list;
	int		listsize;

	listsize = 0;
	tmp_list = status->env;
	while (tmp_list != NULL)
	{
		tmp_list = tmp_list->next;
		listsize++;
	}
	result = (char **)ft_calloc (sizeof(char *), listsize + 1);
	if (result == NULL)
		return (NULL);
	listsize = 0;
	tmp_list = status->env;
	while (tmp_list != NULL)
	{
		result[listsize] = tmp_list->content;
		tmp_list = tmp_list->next;
		listsize++;
	}
	result[listsize] = NULL;
	return (result);
}

void	search_paht_and_exec(t_info *status)
{
	int		fd_nbr;
	char	*path;
	char	**cmd;

	cmd = generate_cmdstr(status);
	path = check_access(status->stack->cmdlist->content, status);
	errno = 0;
	fd_nbr = open(path, O_WRONLY);
	if (path == NULL)
		is_no_file_error(status);
	else if (fd_nbr == -1 && errno == EISDIR)
		is_directory_error(status, path);
	if (access(path, X_OK) != 0)
		is_non_xok(status);
	execve(path, cmd, env_list(status));
	split_free(cmd);
}

void	ex_execve(t_info *status)
{
	pid_t	pid;
	int		exit_status;

	if (status->pipe == 0)
	{
		pid = fork();
		if (pid == -1)
			exit (1);
		if (pid == 0)
		{
			search_paht_and_exec(status);
		}
		wait(&exit_status);
		status->exit_status = WEXITSTATUS(exit_status);
	}
	else
		search_paht_and_exec(status);
	(void)pid;
}
