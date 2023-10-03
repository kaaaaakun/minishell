/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chck_flag_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 18:52:48 by hhino             #+#    #+#             */
/*   Updated: 2023/10/03 12:38:14 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_panda.h"
#include "minishell.h"

void	lexer_panda_error_check(int *flag, t_info *status)
{
	if (*flag & D_QUOTE)
		ft_putendl_fd(" \"minishell: syntax error near unexpected token `\"'",
			1);
	if (*flag & S_QUOTE)
		ft_putendl_fd(" \"minishell: syntax error near unexpected token `\''",
			1);
	if (*flag & NEED_FILE)
		ft_putendl_fd(" \"minishell: syntax error near \
				unexpected token `newline'",
			1);
	if (!(*flag & COMMAND))
		ft_putendl_fd(" \"minishell: syntax error near unexpected token `|'",
			1);
	ft_putendl_fd(" erro check ", 1);
	(void)status;
}
