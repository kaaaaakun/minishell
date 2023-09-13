/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:44:23 by tokazaki          #+#    #+#             */
/*   Updated: 2023/09/13 16:54:17 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ex_pwd(void)
{
	char	*path;
	char	buf[PATH_MAX];

	path = getcwd(buf, PATH_MAX);
	if (path == NULL) //PATH_MAXより長いディレクトリだった場合error
		return ;
	ft_printf("%s\n", buf);
}

//buf,pathをfreeすると死ぬのでいらない
