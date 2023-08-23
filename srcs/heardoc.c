/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heardoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 12:46:48 by tokazaki          #+#    #+#             */
/*   Updated: 2023/08/23 13:13:01 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ex_heardoc(char *line)
{
	char *getline;

	ft_putstr_fd("[heardoc]", 1);
	while (1)
	{
		getline = readline(">");
		if (getline == NULL)
			return ;
		if (ft_strncmp(getline, line, 100) == 0)
			return ;
		free(getline);
	}
}
