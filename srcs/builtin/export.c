/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:14:07 by hhino             #+#    #+#             */
/*   Updated: 2023/09/11 17:41:49 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export_env(t_list *env)
{
	char	*str;

	while (env != NULL)
	{
		str = ft_strjoin("declare -x ", env->content);
		insert_doublequotes(str);
		ft_printf("%s\n", str);
		free(str);
		env = env->next;
	}
}

void	rewrite_envlist(t_list *env, char *str)
{
	t_list	*new;

	new = create_list(str);
	new->next = env->next;
	//new->prev = env->prev;
	free_list(env);
}

void	ex_export(t_info *status, t_stack *data)
{
	int	flag;
	int	i;

	flag = 0;
	i = 0;
	if (data->cmdlist->next == NULL)
		print_export_env(status->env);
	else
	{
		data->cmdlist = data->cmdlist->next;
		while (data->cmdlist != NULL)
		{
			flag = plus_equal_or_not(data->cmdlist->content);
			if (valid_left(data->cmdlist->content, flag) == 0)
				ft_printf("%s not a valid identifier\n", data->cmdlist->content);
			else
			{
				if (flag == 0)
				{
					while (data->cmdlist->content[i] != '+')
						i++;
				}
				else if (flag == 1)
				{
					while (data->cmdlist->content[i] != '=' || data->cmdlist->content[i] != '\0')
						i++;
				}
				if (search_envlist(status, ft_substr(data->cmdlist->content, 0, i))) //0911ここから
					rewrite_envlist(status->env, data->cmdlist->content);
				else
					push_back(&status->env, ft_strdup(data->cmdlist->content));
			}
			data->cmdlist = data->cmdlist->next;
		}
	}
	return ;
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
