/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_operation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:45:05 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/07 19:58:58 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_panda.h"

void	make_input_redirect(int *flag, char *line, int j, t_info *status)
{
	t_stack	*data;
	char	*str;

	data = search_last_stack(status);
	d_printf(" : no*flag redirect", 1);
	str = make_list(flag, line, j, &data->inputlist);
	check_flag(status, str, flag);
	free_null(str);
	*flag = *flag - INPUT_REDIRECT;
}

void	make_output_redirect(int *flag, char *line, int j, t_info *status)
{
	t_stack	*data;
	char	*str;

	data = search_last_stack(status);
	d_printf(" : RE redirect", 1);
	str = make_list(flag, line, j, &data->outputlist);
	check_flag(status, str, flag);
	free_null(str);
	*flag -= OUTPUT_REDIRECT;
}

void	make_heredoc_list(int *flag, char *line, int j, t_info *status)
{
	char	*str;
	t_stack	*data;

	data = search_last_stack(status);
	d_printf(" : heredoc", 1);
	str = mini_substr(line, 0, j);
	str = check_flag(status, str, flag);
	free_null(str);
//	push_back(&data->heredoclist, str);
	*flag -= HEREDOC;
	(void)data;
}

void	make_append_list(int *flag, char *line, int j, t_info *status)
{
	t_stack	*data;
	char	*str;

	data = search_last_stack(status);
	d_printf(" : append", 1);
	str = mini_substr(line, 0, j);
	str = check_flag(status, str, flag);
	free_null(str);
//	push_back(&data->appendlist, str);
	*flag -= APPENDDOC;
	(void)data;
}
