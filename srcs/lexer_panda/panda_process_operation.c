/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panda_process_operation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 19:32:02 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/07 19:56:29 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_panda.h"

int	process_quotes(char *line, int *value, int *i, int *flag)
{
	int	j;

	j = 0;
	while ((analysis_char(line[*i]) == *value || \
		*flag & IN_QUOTE) && line[*i] != '\0')
	{
		if (line[*i] == '\'' && *flag & S_QUOTE)
			*flag -= S_QUOTE;
		else if (line[*i] == '\"' && *flag & D_QUOTE)
			*flag -= D_QUOTE;
		else if (line[*i] == '\'' && !(*flag & IN_QUOTE))
			*flag += S_QUOTE;
		else if (line[*i] == '\"' && !(*flag & IN_QUOTE))
			*flag += D_QUOTE;
		else
			j++;
		*i += 1;
		line[j] = line[*i];
	}
	return (j);
}

int	process_input_redirect_operation(t_info *status, char *line, int *flag)
{
	int	i;

	i = 0;
	while (line[i] == '<')
	{
		d_printf("%c", line[i]);
		i++;
	}
	if (*flag & NEED_FILE || 2 < i)
	{
		*flag = ERROR;
	}
	if (i == 2)
		*flag = *flag | HEREDOC;
	else if (i != 2)
		*flag = *flag | INPUT_REDIRECT;
	return (i);
	(void)status;
}

int	process_output_redirect_operation(t_info *status, char *line, int *flag)
{
	int	i;

	i = 0;
	while (line[i] == '>')
	{
		d_printf("%c", line[i]);
		i++;
	}
	if (*flag & NEED_FILE || 2 < i)
	{
		*flag = ERROR;
	}
	if (i == 2 || (i == 4 && *flag == ERROR))
		*flag = *flag | APPENDDOC;
	else if (i != 2)
		*flag = *flag | OUTPUT_REDIRECT;
	return (i);
	(void)status;
}

int	process_pipe_operation(t_info *status, char *line, int *flag)
{
	int		i;
	t_stack	*data;

	i = 0;
	data = status->stack;
	while (line[i] == '|')
	{
		d_printf("%c", line[i]);
		i++;
	}
	if (1 < i || (*flag & NEED_FILE) || !(*flag & COMMAND))
	{
		*flag += ERROR;
	}
	else if (i == 1)
	{
		check_command(status, status->stack);
	}
	return (i);
	(void)status;
	(void)data;
}
