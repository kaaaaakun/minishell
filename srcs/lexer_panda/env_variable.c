/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 14:14:38 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/07 14:17:50 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"
#include "lexer_panda.h"

char	*check_dollar(t_info *status, char *line)
{
	int		i;
	int		flag;
	int		j;
	char	*result;

	d_printf("[check_dollar]");
	status->line = line;
	i = 0;
	j = 0;
	flag = 0;
	while (line[i] != '\0')
	{
		search_env_variable(line, &i, &flag);
		if (j == 0)
			result = ft_substr(line, j, i - j);
		else
			result = ft_strjoin_free(result, ft_substr(line, j, i - j), \
				FIRST_FREE);
		if (line[i] == '$')
			result = process_dollar(status, result, &i, &flag);
		j = i;
		d_printf("\n[途中 dollar :%s]\n", result);
	}
	d_printf("\n[end dollar :%s]\n", result);
	return (result);
}

void	search_env_variable(char *line, int *i, int *flag)
{
	while ((line[*i] != '$' || *flag & S_QUOTE) && line[*i] != '\0')
	{
		if ((line[*i] == '\'' || line[*i] == '\"') && !(*flag & IN_QUOTE))
			plusle_quote(line[*i], flag);
		else if ((line[*i] == '\'' && *flag & S_QUOTE) || \
			(line[*i] == '\"' && *flag & D_QUOTE))
			minun_quote(line[*i], flag);
		else if (line[*i] == '<' && line[*i + 1] != '<' && !(*flag & IN_QUOTE))
		{
			*flag += INPUT_REDIRECT;
			*i += count_input_heredoc(line, *i, *flag);
		}
		else if (line[*i] == '<' && line[*i + 1] == '<' && !(*flag & IN_QUOTE))
		{
			*flag += HEREDOC;
			*i += count_input_heredoc(line, *i, *flag);
		}
		*i += 1;
	}
}
