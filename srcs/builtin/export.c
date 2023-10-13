/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:14:07 by hhino             #+#    #+#             */
/*   Updated: 2023/10/13 20:43:41 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"

static void	append_envlist(t_list *env, char *str)
{
	char	*temp;
	char	*top;

	temp = env->content;
	top = ft_strchr(str, '=') + 1;
	if (ft_strchr(env->content, '=') != NULL)
		env->content = ft_strjoin_free(env->content, top, FIRST_FREE);
	else
	{
		env->content = ft_strjoin_free(env->content, "=", NEITHER_FREE);
		env->content = ft_strjoin_free(env->content, top, NEITHER_FREE);
	}
	free(str);
	(void)temp;
}

void	overwrite_envlist(t_list *env, char *str)
{
	char	*temp;

	if (!env || !str)
		return ;
	temp = env->content;
	free_null(env->content);
	env->content = str;
	(void)temp;
}

void	execute_export(t_info *status, int flag, char *left, t_list *list)
{
	if (search_envlist_for_export(status, left) != NULL)
	{
		if (flag == 1)
			append_envlist(search_envlist_for_export(status, left),
				ft_strdup(list->content));
		else
			overwrite_envlist(search_envlist_for_export(status, left),
				ft_strdup(list->content));
	}
	else
		push_back_export(flag, status, list);
}

void	core_of_export(t_info *status, t_list *list, int flag)
{
	int		i;
	char	*left;

	if (valid_left(list->content, flag) == 0)
		non_valid_left(status);
	else
	{
		i = 0;
		i = count_left_str(flag, list, i);
		left = ft_substr(list->content, 0, i);
		execute_export(status, flag, left, list);
		free(left);
	}
}

void	ex_export(t_info *status, t_stack *data)
{
	int		flag;
	t_list	*list;

	flag = 0;
	list = data->cmdlist;
	if (list->next == NULL)
		print_export_env(status->env);
	else
	{
		list = list->next;
		while (list != NULL)
		{
			flag = plus_equal_or_not(list->content);
			core_of_export(status, list, flag);
			list = list->next;
		}
	}
	return ;
}

// void	ex_export(t_info *status, t_stack *data)
// {
// 	int		flag;
// 	int		i;
// 	t_list	*list;
// 	char	*left;

// 	flag = 0;
// 	list = data->cmdlist;
// 	if (list->next == NULL)
// 		print_export_env(status->env);
// 	else
// 	{
// 		list = list->next;
// 		while (list != NULL)
// 		{
// 			flag = plus_equal_or_not(list->content);
// 			if (valid_left(list->content, flag) == 0)
// 			{
// 				error_printf(" not a valid identifier\n");
// 				status->exit_status = 1;
// 			}
// 			else
// 			{
// 				i = 0;
// 				if (flag == 1)
// 				{
// 					while (list->content[i] != '+')
// 						i++;
// 				}
// 				else
// 				{
// 					while (list->content[i] != '=' && list->content[i] != '\0')
// 						i++;
// 				}
// 				left = ft_substr(list->content, 0, i);
// 				if (search_envlist_for_export(status, left) != NULL)
// 				{
// 					if (flag == 1)
// 						append_envlist(search_envlist_for_export(status, left),
// 							ft_strdup(list->content));
// 					else
// 						overwrite_envlist(search_envlist_for_export(status,
// 								left), ft_strdup(list->content));
// 				}
// 				else
// 				{
// 					if (flag == 1)
// 						push_back(&status->env,
// 							no_left_but_plus(ft_strdup(list->content)));
// 					else
// 						push_back(&status->env, ft_strdup(list->content));
// 				}
// 				free(left);
// 			}
// 			list = list->next;
// 		}
// 	}
// 	return ;
// }
