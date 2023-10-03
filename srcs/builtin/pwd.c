/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:44:23 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/03 12:48:53 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ex_pwd(void)
{
	char	*path;
	char	buf[PATH_MAX];

	path = getcwd(buf, PATH_MAX);
	if (path == NULL)
		exit (1);
	ft_printf("%s\n", buf);
}
