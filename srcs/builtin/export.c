/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:14:07 by hhino             #+#    #+#             */
/*   Updated: 2023/09/06 21:01:20 by hhino            ###   ########.fr       */
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

	while (env != NULL)
	{
		str = ft_strjoin("declare -x ", env->content);
		insert_doublequotes(str);
		ft_printf("%s\n", str);
		free(str);
		env = env->next;
	}
}

int	check_left(t_list *env, char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '=')
		i++;
	if (i == ft_strlen(str))
		return (0);
	while (env != NULL)
	{
		if (ft_strncmp(env->content, str, i) == 0)
			return (1);
		env = env->next;
	}
	return (0);
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
			if (check_left(status->env, data->cmdlist->content) == 1)
			{
				create_list(ft_strchr(data->cmdlist->content, '='));
				//newlistのnextなどをつなげ直す
				//かつてのenvの中のリストをfreeする
			}
			else
				push_back(&status->env, data->cmdlist->content);
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
