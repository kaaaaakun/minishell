/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmdlist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:47:19 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/07 19:58:37 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_panda.h"

void	make_command_list(int *flag, char *line, int j, t_info *status)
{
	char	*str;
	t_stack	*data;

	data = search_last_stack(status);
	str = make_list(flag, line, j, &data->cmdlist);
	check_flag(status, str, flag);
	*flag = *flag | COMMAND;
}

void	make_other_list(int *flag, char *line, int j, t_info *status)
{
	t_stack	*data;
	char	*str;

	data = search_last_stack(status);
	d_printf(" : *flag or file");
	str = make_list(flag, line, j, &data->cmdlist);
	check_flag(status, str, flag);
}
