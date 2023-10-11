/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:27:12 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/11 14:50:00 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	checkflag(char *str)
{
	if (*str == '-')
	{
		str++;
		while (*str == 'n')
			str++;
		if (*str == '\0')
			return (1);
	}
	return (0);
}

void	ex_echo(t_info *status, t_stack *data)
{
	int		nflag;
	int		flag;
	t_list	*list;

	(void)status;
	flag = 0;
	nflag = 0;
	list = data->cmdlist->next;
	while (list != NULL)
	{
		if (checkflag(list->content) != 0 && flag == 0)
			nflag = 1;
		else
		{
			if (flag != 0)
				ft_putstr_fd(" ", 1);
			ft_putstr_fd(list->content, 1);
			flag = 1;
		}
		list = list->next;
	}
	if (nflag != 1)
		ft_putstr_fd("\n", 1);
	status->exit_status = 0;
}
