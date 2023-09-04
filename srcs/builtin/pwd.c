/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:44:23 by tokazaki          #+#    #+#             */
/*   Updated: 2023/09/04 20:13:22 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ex_pwd(void)
{
	char	*i;
	char	buf[PATH_MAX];

	i = getcwd(buf, PATH_MAX);
	if (i == NULL) //PATH_MAXより長いディレクトリだった場合error
		return ;
	ft_printf("%s\n", buf);
}
