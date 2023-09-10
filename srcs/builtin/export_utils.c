/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 17:06:49 by hhino             #+#    #+#             */
/*   Updated: 2023/09/10 17:08:24 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_doublequotes(char *str)
{
	int		len;
	char	*flag;

	flag = ft_strchr(str, '=');
	len = ft_strlen(str);
	if (flag != NULL)
	{
		ft_memmove(flag + 2, flag + 1, len - (flag - str));
		flag[1] = '"';
	}
	str[len + 1] = '"';
	str[len + 2] = '\0';
}

