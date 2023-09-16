/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:27:53 by tokazaki          #+#    #+#             */
/*   Updated: 2023/09/16 18:10:33 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer(char *line, t_info *status)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		i += lexer_split_and_push(&line[i], status);
	}
}

void	lexer_split(char *line, int *len);
{
	int		count;
	int		flag;
	int		word_type;

	flag = 0;
	count = 0;
	word = lexer_split(line, status);
	word_type = analysis_char(line[count]);
	while ((analysis_char(line[count]) == word_type || IN_QUTE) && line[count] != '\0')
	{
		change_quote(line[count], &flag)
		count++;
	}
	*len = count;
	return (ft_substr(line, 0, count))
}

int	lexer_split_and_make_list(char *line, t_info status);
{
	char	*splited_word;
	int		len;

	len = 0;
	splited_word = lexer_split(line, &len);
	push_back(status->flist, splited_word);
	return (len);
}

//utils+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//引用符のフラグ確認
void	plusle_quote(char s, int *flag)
{
	if (s == '\'')
		*flag += S_QUOTE;
	else if (s == '\"')
		*flag += D_QUOTE;
}

void	minun_quote(char s, int *flag)
{
	if (s == '\'')
		*flag -= S_QUOTE;
	else if (s == '\"')
		*flag -= D_QUOTE;
}

void	change_quote(char s, int *flag)
{
	if (*flag & IN_QUTE)
		minun_quote(s, flag);
	else if (!(*flag & IN_QUTE))
		pulsle_quote(s, flag);
}

/////////////////////////////////////////////////////////////////////
//機能文字の確認
int	analysis_char(char c)
{
//	if (ft_isdigit(c) || ft_isalpha(c) || c =='-' || c =='\"' || c =='\'' || c =='/' || c =='$' || c =='.'|| c =='+' || c =='_')
//		return (1);
	if (c == ' ')
		return (2);
	if (c == '<')
		return (3);
	if (c == '>')
		return (4);
	if (c == '|')
		return (5);
	if (c == '\0')
		return (0);
	return (1);
}
