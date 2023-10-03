/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:55:23 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/03 20:24:09 by tokazaki         ###   ########.fr       */
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

void	search_paht_and_exec(t_info *status)
{
	int		fd_nbr;
	char	*path;
	char	**cmd;

	cmd = generate_cmdstr(status);
	path = check_access(status->stack->cmdlist->content, status);
	errno = 0;
//	d_printf("\n[path %s]",path);
//	d_printf("[%s]",status->stack->cmdlist->content);
	fd_nbr = open(path, O_WRONLY);
	if (path == NULL)//no file
	{
		if (status->stack->cmdlist->content[0] == '.' || status->stack->cmdlist->content[0] == '/')//no file
		{
			error_printf("minishell: %s: No such file or directory\n", status->stack->cmdlist->content);
			exit (127) ;
		}
		error_printf("%s: command not found\n", status->stack->cmdlist->content);
		exit (127) ;
	}
	if (fd_nbr == -1 && errno == EISDIR)//directryの判定用
	{
		if (status->stack->cmdlist->content[0] == '.' || path[0] == '/')//絶対path
		{
			error_printf("%s: is a directory\n", status->stack->cmdlist->content);
			exit (126);
		}
		if (status->stack->cmdlist->content[0] == '/')
		{
			error_printf("minishell: %s: No such file or directory\n", status->stack->cmdlist->content);
			exit(127);
		}
		else
		{
			error_printf("%s: command not found\n", status->stack->cmdlist->content);
			exit (127) ;
		}
	}
	if (access(path, X_OK) != 0)//実行権限がない時
	{
		if (status->stack->cmdlist->content[0] == '.' && status->stack->cmdlist->content[1] == '/')//絶対path
		{
			error_printf("%s: Permission denied\n", status->stack->cmdlist->content);
			exit (126) ;
		}
		if (status->stack->cmdlist->content[0] == '/')//絶対path
		{
			error_printf("minishell: %s: No such file or directory\n", status->stack->cmdlist->content);
			exit (127) ;
		}
		error_printf("%s: command not found\n", status->stack->cmdlist->content);
		exit (127) ;
	}
	else
	{
		execve(path, cmd, NULL);
		error_printf("%s: command not found\n", status->stack->cmdlist->content);
		exit (127) ;
	}
}

void	ex_execve(t_info *status)
{
	pid_t	pid;
	int		exit_status;

	if (status->pipe == 0)//pipeがなかった時
	{
		pid = fork();
		if (pid == -1)
			exit (1);
		if (pid == 0)
		{
			search_paht_and_exec(status);
		}
		wait(&exit_status);
		status->exit_status =WEXITSTATUS(exit_status);
	}
	else//pipeがあった時
	{
		search_paht_and_exec(status);
	}
	(void)pid;
}

