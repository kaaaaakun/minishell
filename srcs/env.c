/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:37:51 by tokazaki          #+#    #+#             */
/*   Updated: 2023/08/19 15:34:52 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

void	env_all(char **env);

void	ex_env(char **split, char **env)
{
	(void)split;
	env_all(env);
//	if (split[1] == NULL)
//		env_all(env);
}

void	env_all(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		ft_putendl_fd(env[i], 1);
		i++;
	}
}
