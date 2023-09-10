/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:14:07 by hhino             #+#    #+#             */
/*   Updated: 2023/09/10 17:08:53 by hhino            ###   ########.fr       */
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

t_list	*check_left_str(t_list *env, char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '=')
		i++;
	if (i == ft_strlen(str))
		return (NULL);
	while (env != NULL)
	{
		if (ft_strncmp(env->content, str, i) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	replace_list(t_list *env, char *str)
{
	t_list	*new;

	new = create_list(str);
	new->next = env->next;
	//new->prev = env->prev;
	free_list(env);
}

int	check_leftinitial(char *str)
{
	if (str[0] != ft_isalpha(str[0]))
		return (1);
	else
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
			if (check_leftinitial(data->cmdlist->content) == 0)
				ft_printf("%s not a valid identifier\n", data->cmdlist->content);
			else
			{
				if (check_left_str(status->env, data->cmdlist->content))
					replace_list(status->env, data->cmdlist->content);
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
