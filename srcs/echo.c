/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:27:12 by tokazaki          #+#    #+#             */
/*   Updated: 2023/08/20 20:10:47 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ex_echo(char **split)
{
	int	i;

	i = 1;
	while (split[i] != NULL)
	{
		if (i != 1)
			ft_putstr_fd(" ", 1);
		ft_putstr_fd(split[i], 1);
		i++;
	}
	ft_putstr_fd("\n", 1);
}
