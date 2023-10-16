/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chck_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 19:33:47 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/15 20:30:33 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_panda.h"

char	*make_first_space_splited_word(char *result, char *post_word, \
	int i, int j)
{
	char	*space_splited_word;

	d_printf("make_first_space_splited_word");
	result = ft_strjoin_free(result, "\'", FIRST_FREE);
	space_splited_word = ft_substr(post_word, 0, i - j);
	result = ft_strjoin_free(result, "\'", FIRST_FREE);
	return (result);
	(void)space_splited_word;
	(void)i;
	(void)j;
	(void)post_word;
}

char	*append_non_quote_env(char *result, char *post_word)
{
	int		start;
	int		end;
	char	*space_splited_word;

	start = 0;
	end = start;
	while (post_word[start] != '\0' && (post_word[start] == ' ' || \
		post_word[start] == '	'))
		post_word++;
	while (post_word[start] != '\0')
	{
		while (post_word[start] != '\0' && post_word[start] != ' ' && \
			post_word[start] != '	')
			start++;
		result = ft_strjoin_free(result, "\'", FIRST_FREE);
		space_splited_word = ft_substr(post_word, end, start - end);
		result = ft_strjoin_free(result, space_splited_word, BOTH_FREE);
		skip_space(post_word, &start);
		if (post_word[start - 1] == ' ' || post_word[start - 1] == '	')
			result = ft_strjoin_free(result, "\' ", FIRST_FREE);
		else
			result = ft_strjoin_free(result, "\'", FIRST_FREE);
		end = start;
	}
	return (result);
}

char	*search_and_append_env(t_info *status, \
			char *result, char *post_word, int *flag)
{
	char	*tmp;

	tmp = post_word;
	d_printf("[s_a_ap_env]\n");
	post_word = search_env(status, post_word);
	if (post_word != NULL)
	{
		if (*flag & D_QUOTE)
			result = ft_strjoin_free(result, post_word, FIRST_FREE);
		else
		{
			result = append_non_quote_env(result, post_word);
		}
	}
	free_null(tmp);
	d_printf("[result:%s]\n", result);
	return (result);
}

char	*process_dollar(t_info *status, char *result, int *i, int *flag)
{
	char	*line;
	int		count;

	line = status->line;
	count = 0;
	if (*flag & HEREDOC)
	{
		count = find_next_token(line, *i, *flag);
		result = ft_strjoin_free(result, \
			ft_substr(&line[*i], 0, count), BOTH_FREE);
	}
	else if (line[*i] == '$' && !(line[*i + 1] == '_' || \
		ft_isdigit(line[*i + 1]) || ft_isalpha(line[*i + 1])))
		result = process_single_double_dollar(status, line, i, result);
	else if (line[*i + 1] == '\"' && *flag & D_QUOTE)
		result = process_single_dollar_in_d_quote(status, line, i, result);
	else
	{
		*i += 1;
		count = find_next_token(line, *i, *flag);
		result = search_and_append_env(status, result, \
			ft_substr(&line[*i], 0, count), flag);
	}
	*i += count;
	return (result);
}
