/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:27:12 by tokazaki          #+#    #+#             */
/*   Updated: 2023/09/03 19:18:32 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	checkflag(char *str)
{
	if (*str == '-')
	{
		str++;
		while (*str == 'n')
			str++;
		if (*str == '\0')
			return (1);//-n
	}
	return (0);//通常
}

void	ex_echo(t_info *status, t_stack *data)
{
	int	i;
	int	nflag;
	int	flag;

	i = 1;
	flag = 0;
	nflag = 0;
	while (data->cmdlist->content != NULL)
	{
		if (checkflag(data->cmdlist->content) != 0 && flag == 0)
			nflag = 1;
		else
		{
			if (flag != 0)
				ft_putstr_fd(" ", 1);
			ft_putstr_fd(data->cmdlist->content, 1);
			flag = 1;
		}
		data->cmdlist->content = data->cmdlist->next->content;
	}
	if (nflag != 1)
		ft_putstr_fd("\n", 1);
}
