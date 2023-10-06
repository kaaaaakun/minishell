/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:14:07 by hhino             #+#    #+#             */
/*   Updated: 2023/10/06 20:11:38 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

static void	append_envlist(t_list *env, char *str)
{
	char	*temp;

	temp = env->content;
	if (ft_strchr(env->content, '=') != NULL)
		env->content = ft_strjoin_free(env->content, \
			ft_strchr(str, '=') + 1, NEITHER_FREE);
	else
	{
		env->content = ft_strjoin_free(env->content, "=", NEITHER_FREE);
		env->content = ft_strjoin_free(env->content, \
			ft_strchr(str, '=') + 1, NEITHER_FREE);
	}
	(void)temp;
}

void	overwrite_envlist(t_list *env, char *str)
{
	char	*temp;

	if (!env || !str)
		return ;
	temp = env->content;
	env->content = str;
	(void)temp;
}

//0912左辺が存在している時に+=をした次の"export"で死ぬ
//export cc=cc -> export cc ->export すると cc になる。でもbashはcc=ccのまま

void	ex_export(t_info *status, t_stack *data)
{
	int		flag;
	int		i;
	t_list	*list;
	char	*listcontent;

	flag = 0;
	list = data->cmdlist;
	listcontent = list->content;
	if (list->next == NULL)
		print_export_env(status->env);
	else
	{
		list = list->next;
		while (list != NULL)
		{
			flag = plus_equal_or_not(list->content);
			if (valid_left(list->content, flag) == 0)
			{
				error_printf(" not a valid identifier\n");
				status->exit_status = 1;
			}
			else
			{
				i = 0;
				if (flag == 1)
				{
					while (list->content[i] != '+')
						i++;
				}
				else
				{
					while (list->content[i] != '=' && list->content[i] != '\0')
						i++;
				}
				if (search_envlist_for_export(status, \
						ft_substr(list->content, 0, i)) != NULL)
				{
					if (flag == 1)
						append_envlist(search_envlist_for_export(status, \
							ft_substr(list->content, 0, i)), \
								ft_strdup(list->content));
					else
						overwrite_envlist(search_envlist_for_export(status, \
							ft_substr(list->content, 0, i)), \
								ft_strdup(list->content));
				}
				else
				{
					if (flag == 1)
						push_back(&status->env, \
							no_left_but_plus(ft_strdup(list->content)));
					else
						push_back(&status->env, ft_strdup(list->content));
				}
			}
			list = list->next;
		}
	}
	return ;
	(void)listcontent;
}


// bash-3.2$ export aaa=bbb
// bash-3.2$ export ccc="echo $aaa"
// bash-3.2$ $ccc
// bbb
// bash-3.2$ export aaa=bbb ccc
// bash-3.2$ export ccc="echo $aaa"
// bash-3.2$ $ccc
// bbb
// $の後にくるものは英数字と_のみ
// $$(必須ではない、プロセスID), $?(必須、終了ステータス)
// 左辺が以前に定義したものと同値であれば=以下を書き換える
// 左辺の一文字目が英字以外だった場合は弾かれるが、引数がその後も続く場合は反映される
// export PATH=$PATH:/path/to/new/program
