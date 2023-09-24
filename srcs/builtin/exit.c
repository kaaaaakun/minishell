/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 20:11:54 by tokazaki          #+#    #+#             */
/*   Updated: 2023/09/24 16:03:29 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ex_exit(t_info *status, t_stack *data)
{
	t_list	*list;

	list = data->cmdlist;
	if (list == NULL || status == NULL || list->next == NULL
		|| ft_memcmp(list->next->content, "--", 3))
	{
		ft_putendl_fd("exit", 1);
		exit(0);
	}
	else if (ft_str_is_num(list->next->content) == 1)
	{
		status->exit_status = ft_atoi(list->next->content);
		ft_putendl_fd("exit", 1);
		exit(0);
	}
	else if (!ft_str_is_num(list->next->content) == 0)
	{
		ft_printf("%s: ", list->next->content);
		ft_putendl_fd("numeric argument required", 1);
		ft_putendl_fd("exit", 1);
		exit(0);
	}
}

// atoi
// str_is_num

// t_info->exit_statusに数字を入れる
// 0~255
// exit aa -> numeric argument required -> exit
// exit \ -> 一度enter押してからexit
// exit -+0 -> numeric argument required -> exit
// exit "" -> numeric argument required -> exit
// exit # -> exit
// exit ## -> exit
// exit !'" -> event not found -> bash
// exit ! -> numeric argument required -> exit
// exit '" -> >' -> numeric argument required -> exit
// exit ' -> >123 -> >' -> numeric argument required -> exit //\nが入るため
// exit "123" -> exit
// exit ' -> >123' -> exit
// exit -- -> exit
