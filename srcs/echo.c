/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:27:12 by tokazaki          #+#    #+#             */
/*   Updated: 2023/08/19 17:41:13 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

void	ex_echo(char **split)
{
	int	i;

	i = 2;
	ft_putstr_fd(split[1], 1);
	while (split[i] != NULL)
	{
		ft_putstr_fd(" ", 1);
		ft_putstr_fd(split[i], 1);
		i++;
	}
}
