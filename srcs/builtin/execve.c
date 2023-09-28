/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 12:55:23 by tokazaki          #+#    #+#             */
/*   Updated: 2023/09/28 18:44:37 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"
#include "typedef_struct.h"

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

void	ex_execve(t_info *status)
{
	int		pid;
	int		exit_status;
	char	*path;
	char	**cmd;

	if (status->pipe == 0)//pipeがなかった時
	{
		pid = fork();
		if (pid == 0)
		{
			cmd = generate_cmdstr(status);
			path = check_access(status->stack->cmdlist->content, status);
			if (path == NULL)
			{
				error_printf("command not found: %s\n", status->stack->cmdlist->content);
				exit (127) ;
			}
			execve(path, cmd, NULL);
		}
		waitpid(pid, &exit_status, 0);
		error_printf("[%d]\n", status);
		status->exit_status = exit_status;
	}
	else//pipeがあった時
	{
		cmd = generate_cmdstr(status);
		path = check_access(status->stack->cmdlist->content, status);
		if (path == NULL)
		{
			error_printf("command not found: %s\n", status->stack->cmdlist->content);
			exit (127) ;
		}
		execve(path, cmd, NULL);
	}
	(void)pid;
}

