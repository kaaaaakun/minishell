/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:15:57 by hhino             #+#    #+#             */
/*   Updated: 2023/10/03 18:05:36 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ex_cd(t_info *status, t_stack *data)
{
	t_list	*list;

	list = data->cmdlist->next;
	if (list == NULL || ft_memcmp(list->content, "~", 2) == 0)
	{
		if (search_env(status, "HOME") != NULL)
			chdir(search_env(status, "HOME"));
		else
		{
			error_printf("cd: HOME not set\n");
			status->exit_status = 1;
		}
	}
	else if (check_access(list->content, status) != NULL)
		chdir(list->content);
	else if (check_access(list->content, status) == NULL)
	{
		error_printf("%s: No such file or directory\n", list->content);
		status->exit_status = 1;
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

