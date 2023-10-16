/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_find_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:32:50 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/15 20:31:09 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_panda.h"

int	find_next_token(char *line, int i, int flag)
{
	int	k;

	k = 0;
	while (line[i + k] != '\'' && line[i + k] != ':' && line[i + k] != '\"' \
			&& line[i + k] != '\t' && \
		line[i + k] != ' ' && line[i + k] != '\0' && (line[i + k] != '$' || \
		flag & HEREDOC) && \
		((line[i + k] != '<' && line[i + k] != '>' && line[i + k] != '|') || \
		(flag & D_QUOTE)))
		k++;
	d_printf("[find_next_token:%d %c]", k, line[i + k]);
	return (k);
}

char	*process_single_dollar_in_d_quote(t_info *status, char *line, \
	int *i, char *result)
{
	result = ft_strjoin_free(result, "$", FIRST_FREE);
	*i += 1;
	return (result);
	(void)status;
	(void)line;
}

char	*process_single_double_dollar(t_info *status, \
	char *line, int *i, char *result)
{
	char	*exit_nbr;
	char	*tmp;

	d_printf("[process_single_double_dollar]");
	if (line[*i] == '$' && line[*i + 1] == '$')
	{
		result = ft_strjoin_free(result, "PID", FIRST_FREE);
		*i += 2;
	}
	else if (line[*i] == '$' && line[*i + 1] == '?')
	{
		tmp = result;
		result = ft_strdup(result);
		exit_nbr = ft_itoa(status->exit_status);
		result = ft_strjoin_free(result, exit_nbr, BOTH_FREE);
		*i += 2;
		free(tmp);
	}
	else
	{
		result = ft_strjoin_free(result, "$", FIRST_FREE);
		*i += 1;
	}
	return (result);
	(void)status;
}

int	analysis_char(char c)
{
	if (ft_isdigit(c) || ft_isalpha(c) || c == '-' || c == '\"' || c == '\'' \
		|| c == '/' || c == '$' || c == '.' || c == '+' || c == '_')
		return (1);
	if (c == ' ' || c == '	')
		return (2);
	if (c == '<')
		return (3);
	if (c == '>')
		return (4);
	if (c == '|')
		return (6);
	if (c == '\0')
		return (7);
	return (1);
}
