/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heardoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 12:46:48 by tokazaki          #+#    #+#             */
/*   Updated: 2023/08/23 18:18:52 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ex_heredoc(char *line)
{
	char *getline;

	ft_putstr_fd("[heredoc]", 1);
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
