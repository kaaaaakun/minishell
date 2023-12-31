/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panda_pre_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 13:49:24 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/15 19:37:29 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_panda.h"

void	check_input_operation(t_info *status, char *line, int j, int *flag)
{
	if (*flag & AT_PIPE)
		*flag -= AT_PIPE;
	if (*flag & INPUT_REDIRECT)
		*flag -= INPUT_REDIRECT;
	else if (*flag & OUTPUT_REDIRECT)
		*flag -= OUTPUT_REDIRECT;
	else if (*flag & HEREDOC)
		*flag -= HEREDOC;
	else if (*flag & APPENDDOC)
		*flag -= APPENDDOC;
	else if (!(*flag & COMMAND))
		*flag += COMMAND;
	(void)j;
	(void)status;
	(void)line;
}

int	skip_count_quotes(char *line, int *value, int *i, int *flag)
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
	}
	return (j);
}

void	check_error(t_info *status, char *line, int *e_flag)
{
	int	i;
	int	j;
	int	value;

	*e_flag = INITIAL;
	while (*line != '\0' && !(*e_flag & ERROR))
	{
		d_printf("[check_erro line : %s]\n", line);
		i = 0;
		value = analysis_char(*line);
		if (value == 1 || value == 0)
		{
			j = skip_count_quotes(line, &value, &i, e_flag);
			check_input_operation(status, line, j, e_flag);
		}
		else if (value == 2)
			i++;
		else if (!(*e_flag & IN_QUOTE))
		i += count_other_operation(status, line, e_flag, value);
		line += i;
		if (*e_flag & ERROR)
			break ;
	}
	if ((*e_flag & NEED_FILE || *e_flag & IN_QUOTE) && !(*e_flag & ERROR))
			*e_flag += ERROR;
}
