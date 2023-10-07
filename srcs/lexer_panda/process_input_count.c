/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input_count.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 15:59:32 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/07 16:39:51 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_panda.h"

int		count_other_operation(t_info *status, char *line, int *flag, int value);
void	process_input_operation(t_info *status, char *line, int j, int *flag);

int	count_other_operation(t_info *status, char *line, int *flag, int value)
{
	int	count;

	count = 0;
	if (value == 3 && !(*flag & IN_QUOTE))
		count += process_input_redirect_operation(status, line, flag);
	else if (value == 4 && !(*flag & IN_QUOTE))
		count += process_output_redirect_operation(status, line, flag);
	else if (value == 6 && !(*flag & IN_QUOTE))
		count += check_pipe_operation(status, line, flag);
	return (count);
}

void	process_input_operation(t_info *status, char *line, int j, int *flag)
{
	if (*flag & INPUT_REDIRECT)
		make_input_redirect(flag, line, j, status);
	else if (*flag & OUTPUT_REDIRECT)
		make_output_redirect(flag, line, j, status);
	else if (*flag & HEREDOC)
		make_heredoc_list(flag, line, j, status);
	else if (*flag & APPENDDOC)
		make_append_list(flag, line, j, status);
	else if (!(*flag & COMMAND))
		make_command_list(flag, line, j, status);
	else
		make_other_list(flag, line, j, status);
}
