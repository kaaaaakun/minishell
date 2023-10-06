/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:55:23 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/06 20:34:07 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"
#include "typedef_struct.h"
#include <errno.h>

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

void	erro_msg_no_such_file(t_info *status, char *content)
{
	error_printf("minishell: %s: No such file or directory\n", content);
	exit (127);
	(void)status;
}

void	erro_msg_is_a_directory(t_info *status, char *content)
{
	error_printf("%s: is a directory\n", content);
	exit (126);
	(void)status;
}

void	erro_msg_permission_denied(t_info *status, char *content)
{
	error_printf("%s: Permission denied\n", content);
	exit (126);
	(void)status;
}

void	erro_msg_not_command_found(t_info *status, char *content)
{
	error_printf("%s: command not found\n", content);
	exit (127);
	(void)status;
}

void	is_no_file_error(t_info *status)
{
	char	*content;

	content = status->stack->cmdlist->content;
	if (content[0] == '.' || content[0] == '/')
		erro_msg_no_such_file(status, content);
	else
		erro_msg_not_command_found(status, content);
}

void	is_directory_error(t_info *status, char *path)
{
	char	*content;

	content = status->stack->cmdlist->content;
	if (content[0] == '.' || path[0] == '/')
		erro_msg_is_a_directory(status, content);
	if (content[0] == '/')
		erro_msg_no_such_file(status, content);
	else
		erro_msg_not_command_found(status, content);
}

void	is_non_xok(t_info *status)
{
	char	*content;

	content = status->stack->cmdlist->content;
	if (content[0] == '.' && content[1] == '/')
		erro_msg_permission_denied(status, content);
	if (content[0] == '/')
		erro_msg_no_such_file(status, content);
	else
		erro_msg_not_command_found(status, content);
}

void	search_paht_and_exec(t_info *status)
{
	int		fd_nbr;
	char	*path;
	char	**cmd;
	char	*content;

	content = status->stack->cmdlist->content;
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
	execve(path, cmd, NULL);
	erro_msg_not_command_found(status, content);
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
