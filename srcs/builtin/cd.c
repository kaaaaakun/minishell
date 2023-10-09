/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:15:57 by hhino             #+#    #+#             */
/*   Updated: 2023/10/09 21:23:16 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"
#include <sys/errno.h>

void	ex_cd(t_info *status, t_stack *data)
{
	t_list	*list;
	char	*path;
	char	buf[PATH_MAX];

	list = data->cmdlist->next;
	if (list == NULL || ft_memcmp(list->content, "~", 2) == 0)
	{
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
		return ;
	}
	path = check_access(list->content, status);
	if (path == NULL)
	{
		error_printf("%s: No such file or directory\n", list->content);
		status->exit_status = 1;
	}
	else if (path != NULL)
	{
		if (access(path, X_OK) != 0)
		{
			error_printf("Permission denied\n");
			status->exit_status = 1;
			free_null(path);
		}
		else
		{
			free_null(path);
			errno = 0;
			if (chdir(list->content) == -1)
			{
				status->exit_status = 1;
				if (errno == EACCES)
				{
					error_printf("Permission denied\n");
				}
				else
				{
					if (list->content[0] == '\0')
					{
						status->exit_status = 0;
						return ;
					}
					error_printf("%s: No such file or directory\n", list->content);
				}
				return ;
			}
			path = getcwd(buf, PATH_MAX);
			if (!path)
				return ;
			overwrite_envlist(search_envlist(status, "PWD"), \
				ft_strjoin("PWD=", buf));
			status->exit_status = 0;
		}
	}
	return ;
}
// cd はHOMEに戻る
// cd /は一番最初の階層に戻る
// cd ../ 存在しないディレクトリ名　はcd ../のみ実行される
// cd ../存在しないディレクトリ名　はエラー
//d---------   3 hhino  2020  102 Aug 31 18:37 test/
	//bash-3.2$ cd test/
	//bash: cd: test/: Permission denied
//dr--------   3 hhino  2020  102 Aug 31 18:37 test/
	//bash-3.2$ cd test/
	//bash: cd: test/: Permission denied
//d-w-------   3 hhino  2020  102 Aug 31 18:37 test/
	//bash-3.2$ cd test/
	//bash: cd: test/: Permission denied
//d--x------   3 hhino  2020  102 Aug 31 18:37 test/
	//bash-3.2$ cd test/
//bash-3.2$ cd ../ 1234 | touch a
	//bash-3.2$ ls
	//a          cd/        minishell/ test/
//minishellのような実行ファイル Not a directory
//chmod -x ?? Permission denied
