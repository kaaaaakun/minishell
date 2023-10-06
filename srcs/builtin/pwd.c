/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:44:23 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/05 18:10:59 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ex_pwd(void)
{
	char	*path;
	char	buf[PATH_MAX];

	path = getcwd(buf, PATH_MAX);
	if (path == NULL)
	{
		perror("pwd");
		exit (1);
	}
	ft_printf("%s\n", buf);
}

//自分のいるdirが消された時PATHから取ってくる
//env PWDを更新する必要がある
