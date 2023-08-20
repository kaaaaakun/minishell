/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:37:51 by tokazaki          #+#    #+#             */
/*   Updated: 2023/08/20 21:02:31 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_env(void);

void	ex_env(char **split)
{
	(void)split;
	write_env();
//	if (split[1] == NULL)
//		env_all(env);
}

void	write_env(void)
{
	int			i;
	extern char	**environ;

	i = 0;
	while (environ[i] != NULL)
	{
		ft_putendl_fd(environ[i], 1);
		i++;
	}
}
