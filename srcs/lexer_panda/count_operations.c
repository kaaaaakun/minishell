/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 19:25:52 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/12 20:32:19 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_panda.h"

int	count_pipe(t_info *status, char *line)
{
	int	count;
	int	flag;
	int	i;

	d_printf("[count_pipe]");
	count = 0;
	flag = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (flag & IN_QUOTE)
				minun_quote(line[i], &flag);
			else if (!(flag & IN_QUOTE))
				plusle_quote(line[i], &flag);
		}
		else if (!(flag & IN_QUOTE) && line[i] == '|')
			count++;
		i++;
	}
	return (count);
	(void)status;
}

int	check_and_count_pipe(t_info *status, char *line)
{
	int	count;

	d_printf("[check_and_count_pipe]");
	count = count_pipe(status, line);
	d_printf("[pipe:count:%d]", count);
	return (count);
	(void)status;
}

int	count_input_heredoc(char *line, int i, int flag)
{
	int	count;

	count = 0;
	if (flag & INPUT_REDIRECT)
		count = 0;
	else if (flag & HEREDOC)
		count += 1;
	while (analysis_char(line[i + count]) == 2)
		count++;
	while (ft_isdigit(line[i + count]) == 1 || \
		ft_isalpha(line[i + count]) == 1 || line[i + count] == '_')
		count++;
	return (count);
}

int	check_pipe_operation(t_info *status, char *line, int *flag)
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
	if (1 < i || (*flag & NEED_FILE) || *flag & AT_PIPE)
	{
		*flag += ERROR;
	}
	else if (i == 1)
	{
		d_printf(" : pipe");
		*flag += AT_PIPE;
	}
	return (i);
	(void)status;
	(void)data;
}
