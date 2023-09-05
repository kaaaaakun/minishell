/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:14:07 by hhino             #+#    #+#             */
/*   Updated: 2023/09/05 20:52:30 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	insert_doublequotes(char *str)
{
	int		len;
	char	*flag;

	flag = ft_strchr(str, '=');
	len = ft_strlen(str);
	if (flag != NULL)
	{
		ft_memmove(flag + 2, flag + 1, len - (flag - str));
		flag[1] = '"';
	}
	str[len + 1] = '"';
	str[len + 2] = '\0';
}

void	print_export_env(t_list *env)
{
	char	*str;

	while (env->next != NULL)
	{
		str = ft_strjoin("declare -x ", env->content);
		insert_doublequotes(str);
		ft_printf("%s\n", str);
		free(str);
		env = env->next;
	}
}

void	ex_export(t_info *status, t_stack *data)
{
	if (data->cmdlist->next == NULL)
		print_export_env(status->env);
	else
	{
		data->cmdlist = data->cmdlist->next;
		while (data->cmdlist != NULL)
		{
			push_back(&status->env, data->cmdlist->content);
			data->cmdlist = data->cmdlist->next;
		}
	}
	return ;
}

//exportの後何もついていない場合は、declare -xを先頭につけ、=以下の文字列を""で囲む処理をする
//=の後に',"がついていない場合、spで区切られる前の文字列までのみ認識される
// bash-3.2$ export aaa=bbb
// bash-3.2$ export ccc="echo $aaa"
// bash-3.2$ $ccc
// bbb
// bash-3.2$ export aaa=bbb ccc
// bash-3.2$ export ccc="echo $aaa"
// bash-3.2$ $ccc
// bbb
// $の後にくるものは英数字と_
// $$(必須ではない、プロセスID), $?(必須、終了ステータス)
