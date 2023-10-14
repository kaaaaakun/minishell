/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:15:57 by hhino             #+#    #+#             */
/*   Updated: 2023/10/12 21:13:52 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"
#include <sys/errno.h>

static void	ex_cd_x_ng(t_info *status, char *path)
{
	error_printf("Permission denied\n");
	status->exit_status = 1;
	free_null(path);
}

static void	ex_cd_error(t_info *status, t_stack *data)
{
	t_list	*list;

	list = data->cmdlist->next;
	status->exit_status = 1;
	if (errno == EACCES)
		error_printf("Permission denied\n");
	else
	{
		if (list->content[0] == '\0')
			status->exit_status = 0;
		else
			error_printf("%s: No such file or directory\n", list->content);
	}
	(void)list;
}

static void	ex_cd_somewhere(t_info *status, t_stack *data)
{
	t_list	*list;
	char	*path;
	char	buf[PATH_MAX];

	list = data->cmdlist->next;
	path = check_access(list->content, status);
	if (access(path, X_OK) != 0)
		ex_cd_x_ng(status, path);
	else
	{
		free_null(path);
		errno = 0;
		if (chdir(list->content) == -1)
		{
			ex_cd_error(status, data);
			return ;
		}
		path = getcwd(buf, PATH_MAX);
		if (!path)
			return ;
		overwrite_envlist(search_envlist(status, "PWD"), ft_strjoin("PWD=",
				buf));
		status->exit_status = 0;
	}
}

static void	ex_cd_home(t_info *status, t_stack *data)
{
	t_list	*list;

	list = data->cmdlist->next;
	if (search_env(status, "HOME") != NULL)
	{
		if (chdir(search_env(status, "HOME")) == -1)
		{
			error_printf("Permission denied\n");
			status->exit_status = 1;
		}
		else
			status->exit_status = 0;
	}
	else
	{
		error_printf("cd: HOME not set\n");
		status->exit_status = 1;
	}
	(void)list;
}

void	ex_cd(t_info *status, t_stack *data)
{
	t_list	*list;
	char	*path;

	list = data->cmdlist->next;
	if (list == NULL || ft_memcmp(list->content, "~", 2) == 0)
	{
		ex_cd_home(status, data);
		return ;
	}
	path = check_access(list->content, status);
	if (path == NULL)
	{
		error_printf("%s: No such file or directory\n", list->content);
		status->exit_status = 1;
	}
	else if (path != NULL)
		ex_cd_somewhere(status, data);
	free_null(path);
	return ;
}
