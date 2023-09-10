/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:15:57 by hhino             #+#    #+#             */
/*   Updated: 2023/09/10 10:49:01 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ex_cd(t_info *status, t_stack *data)
{
	char	*path_name;

	// d_printf("\n[HOME:%s]\n", serch_env(status, "HOME"));
	// d_printf("\n[current:%s]\n", data->cmdlist->content);
	// d_printf("[next:%s]\n", data->cmdlist->next->content);
	// d_printf("[next next:%s]\n", data->cmdlist->next->next->content);
	path_name = malloc(sizeof(char) * PATH_MAX);
	if (data->cmdlist->next == NULL)
		chdir(serch_env(status, "HOME"));
	else if (check_access(data->cmdlist->next->content, status))
		chdir(data->cmdlist->next->content);
	else
		return ; //本当はエラーにして子プロセス終了させたい
	getcwd(path_name, PATH_MAX);
	// d_printf("\n%s\n", path_name);
	free(path_name);
	// free_stack(data); //freeできてた
	// d_printf("\n------------\n");
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

