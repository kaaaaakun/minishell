/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 20:11:54 by tokazaki          #+#    #+#             */
/*   Updated: 2023/09/27 14:41:35 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ex_exit(t_info *status, t_stack *data)
{
	t_list	*list;

	if (status->line == NULL)
	{
		ft_printf("exit", 0);
		exit(0);
	}
	list = data->cmdlist;
	if (list == NULL || status == NULL || list->next == NULL
		|| ft_memcmp(list->next->content, "--", 3) == 0)
	{
		ft_putendl_fd("exit", 1);
		exit(0);
	}
	else if (ft_str_is_num(list->next->content) == 1)
	{
		status->exit_status = ft_atoi(list->next->content) % 256;
		ft_putendl_fd("exit", 1);
		exit(status->exit_status);
	}
	else if (ft_str_is_num(list->next->content) == 0)
	{
		ft_printf("%s: ", list->next->content);
		ft_putendl_fd("numeric argument required", 1);
		ft_putendl_fd("exit", 1);
		exit(0);
	}
}
