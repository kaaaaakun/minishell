/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:44:23 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/07 19:17:11 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ex_pwd(t_info *status, t_stack *data)
{
	char	*path;
	char	buf[PATH_MAX];

	(void)data;
	path = getcwd(buf, PATH_MAX);
	if (path == NULL)
	{
		if (search_envlist(status, "PWD") == NULL)
			error_printf("PWD is not set.\n");
		else
			ft_printf("%s\n", ft_strchr(search_envlist(status, \
				"PWD")->content, '=') + 1);
	}
	else
		ft_printf("%s\n", buf);
}
