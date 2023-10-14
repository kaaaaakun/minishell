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
	status->exit_status = 2;
	if (*flag & D_QUOTE)
		ft_putendl_fd("minishell: syntax error near unexpected token `\"'",
			2);
	else if (*flag & S_QUOTE)
		ft_putendl_fd("minishell: syntax error near unexpected token `\''",
			2);
	else if (*flag & INPUT_REDIRECT)
		ft_putendl_fd("minishell: syntax error near unexpected token `<'",
			2);
	else if (*flag & HEREDOC)
		ft_putendl_fd("minishell: syntax error near unexpected token `<<'",
			2);
	else if (*flag & APPENDDOC)
		ft_putendl_fd("minishell: syntax error near unexpected token `>>'",
			2);
	else if (*flag & OUTPUT_REDIRECT)
		ft_putendl_fd("minishell: syntax error near unexpected token `>'",
			2);
	else if (*flag & AT_PIPE)
		ft_putendl_fd("minishell: syntax error near unexpected token `|'",
			2);
}
