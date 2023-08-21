/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:27:12 by tokazaki          #+#    #+#             */
/*   Updated: 2023/08/21 14:18:44 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	checkflag(char *str)
{
	(void)str;
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

void	ex_echo(char **split)
{
	int	i;
	int	nflag;
	int	flag;
	extern char	**environ;

	i = 1;
	flag = 0;
	nflag = 0;
	while (split[i] != NULL)
	{
		if (checkflag(split[i]) != 0 && flag == 0)
		{
			nflag = 1;
		}
		else
		{
			if (flag != 0)
				ft_putstr_fd(" ", 1);
			ft_putstr_fd(split[i], 1);
			flag = 1;
		}
		i++;
	}
	if (nflag != 1)
		ft_putstr_fd("\n", 1);
}
