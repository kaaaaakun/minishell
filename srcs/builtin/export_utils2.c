/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 20:18:01 by hhino             #+#    #+#             */
/*   Updated: 2023/10/13 20:43:37 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "minishell.h"

int	count_left_str(int flag, t_list *list, int i)
{
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
	return (i);
}

void	push_back_export(int flag, t_info *status, t_list *list)
{
	if (flag == 1)
		push_back(&status->env, no_left_but_plus(ft_strdup(list->content)));
	else
		push_back(&status->env, ft_strdup(list->content));
}

void	non_valid_left(t_info *status)
{
	error_printf(" not a valid identifier\n");
	status->exit_status = 1;
}
