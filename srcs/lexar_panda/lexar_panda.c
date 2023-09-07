/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexar_panda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 17:48:21 by tokazaki          #+#    #+#             */
/*   Updated: 2023/09/06 21:01:44 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexar_panda.h"

int	analysis_char(char c)
{
	if (ft_isdigit(c) || ft_isalpha(c) || c =='-' || c =='\"' || c =='\'' || c =='/' || c =='$' || c =='=')
		return (1);
	if (c == ' ')
		return (2);
	if (c == '<')
		return (3);
	if (c == '>')
		return (4);
//	if (c == '$')
//		return (5);
	if (c == '|')
		return (6);
//	if (c == '\"')
//		return (7);
//	if (c == '\'')
//		return (8);
//	if (c == ';')
//		return (10);
	return (0);
}

int	is_function_word(char c)
{
	int	value;

	value = analysis_char(c);
	if (value == 3)
		return (1);
	if (value == 4)
		return (1);
	if (value == 6)
		return (1);
	return (0);
}

char	*check_dollar(t_info *status, char *line)
{
	ft_printf("[check_dollar]");
	int	i;
	int	flag;
	int	j;
	char	*result;

	i = 0;
	j = 0;
	flag = 0;
	result = line;
	while (1)
	{
		while (line[i] != '$' || flag & S_QUOTE)
		{
			if (line[i] == '\0')//null文字break;
				break ;
			else if ((line[i] == '\'' || line[i] == '\"') && !(flag & IN_QUOTE))
			{
				if (line[i] == '\'')
					flag += S_QUOTE;
				else if (line[i] == '\"')
					flag += D_QUOTE;
				i++;
			}
			else if ((line[i] == '\'' && flag & S_QUOTE) || (line[i] == '\"' && flag & D_QUOTE))
			{
				if (line[i] == '\'')
					flag -= S_QUOTE;
				else if (line[i] == '\"')
					flag -= D_QUOTE;
				i++;
			}
			else
				i++;
			ft_printf("[fline:%d;%c]\n", i, line[i]);
		}
		if (j == 0)
		{
			result = ft_substr(line, j, i - j);
			ft_printf("\n\n\n[j = 0result:%s]",ft_substr(line, j, i - j));
		}
		else
		{
			result = ft_strjoin(result, ft_substr(line, j, i - j));
			ft_printf("\n\n\n[j != 0result:%s]",ft_substr(line, j, i - j));
			ft_printf("[i:%d/j:%d]",i,i - j);
			ft_printf("[eline:%d;%c]\n", i, &line[i]);
		}

	ft_printf("\n[間line:%d;%c]\n", i, line[i]);
		if (line[i] == '$' && (line[i + 1] == '\0' && line[i + 1] == ' '))
		{
			result = ft_strjoin(result, "$");
			ft_printf("\n\n\n[j != 0result:%s]",ft_substr(line, j, i - j));
			ft_printf("[dline:%d;%c]\n", i, line[i]);
			i++;
		}
		else if (line[i] == '$' && line[i + 1] == '$')
		{
			result = ft_strjoin(result, "PID");
			ft_printf("[cline:%d;%c]\n", i, line[i]);
			i += 2;
		}
		else if (line[i] == '$')
		{
			i++;
			ft_printf("\n\n\n[result:%s]",result);
			ft_printf("[bline:%d;%c]\n", i, line[i]);
			char	*pre_word;
			int		k;

			k = 0;
			while (line[i + k] != '\"' && line[i + k] != '\0' && line[i + k] != '$' && ((line[i + k] != '\'' && line[i + k] != ' ' && line[i + k] != '<' && line[i + k] != '>' && line[i + k] != '|') || (flag & D_QUOTE)))
			{
				ft_printf("%c", line[i + k]);
				k++;
			}
			//if (k == 0)
			//	break ;
			if (*result == '\0')
			{
				pre_word = ft_substr(&line[i], 0, k);
				pre_word = serch_env(status, pre_word);
				if (pre_word != NULL)
					result = pre_word;
				ft_printf("\n[result=0:%s]",result);
			}
			else
			{
				pre_word = ft_substr(&line[i], 0, k);
				pre_word = serch_env(status, pre_word);
		ft_printf("\n[pre-word:%s]",pre_word);
		ft_printf("\n[result:%s]",result);
				if (pre_word != NULL)
					result = ft_strjoin(result, pre_word);
			ft_printf("\n[af join esult:%s]",result);
			}
			ft_printf("[i:%d/k:%d]",i,k);
			i += k;
			ft_printf("[aline:%d;%c]\n", i, &line[i]);
		}
		if (line[i] == '\0')//null文字break;
			break ;
		j = i;
	}
	return (result);
}

void	panda(char *line, t_info *status)
{
	ft_printf("[panda]");
	int	i;
	int	value;
	int	flag;
	t_stack	*data;
	char *str;

	flag = INITIAL;
	if (*line == '\0')
		return ;
	ft_printf("\n[%s]\n", line);
	data = make_stack(status, NULL);
	line = check_dollar(status, line);
	ft_printf("\n[%s]\n", line);
	while(*line != '\0')
	{
		i = 0;
		value = -1;
		value = analysis_char(*line);
		if (value == 1) // noflags
		{
//			i = check_noflag_word(&line[i], &flag, status);
			while ((analysis_char(line[i]) == value || flag & IN_QUOTE) && line[i] != '\0')
			{
				ft_printf("%c", line[i]);
				i++;
				if (line[i] == '\'' && flag & S_QUOTE)
				{
					flag-= S_QUOTE;
					i++;
				}
				if (line[i] == '\"' && flag & D_QUOTE)
				{
					flag -= D_QUOTE;
					i++;
				}
				if (line[i] == '\'' && !(flag & IN_QUOTE))
				{
					flag += S_QUOTE;
					i++;
				}
				if (line[i] == '\"' && !(flag & IN_QUOTE))
				{
					flag += D_QUOTE;
					i++;
				}
			}
			if (flag & INPUT_REDIRECT)
			{
				ft_putendl_fd(" : noflag redirect", 1);
				str = make_list(&flag, line, i, &data->inputlist);
				check_flag(status, str, &flag);
				flag = flag - INPUT_REDIRECT;
			}
			else if (flag & OUTPUT_REDIRECT)
			{
				ft_putendl_fd(" : RE redirect", 1);
				str = make_list(&flag, line, i, &data->outputlist);
				check_flag(status, str, &flag);
				flag -= OUTPUT_REDIRECT;
			}
			else if (flag & HEREDOC)
			{
				ft_putendl_fd(" : heredoc", 1);
				str = make_list(&flag, line, i, &data->heredoclist);
				check_flag(status, str, &flag);
				flag -= HEREDOC;
			}
			else if (flag & APPENDDOC)
			{
				ft_putendl_fd(" : append", 1);
				str = make_list(&flag, line, i, &data->appendlist);
				check_flag(status, str, &flag);
				flag -= APPENDDOC;
			}
			else if (!(flag & COMMAND))
			{
				ft_putendl_fd(" : noflag command", 1);
				str = make_list(&flag, line, i, &data->cmdlist);
				check_flag(status, str, &flag);
				flag = flag | COMMAND;
			}
			else
			{
				ft_putendl_fd(" : flag or file", 1);
				str = make_list(&flag, line, i, &data->cmdlist);
				check_flag(status, str, &flag);
			}
		}
		else if (value == 2)// ' '
		{
			while (analysis_char(line[i]) == value)
				i++;
		}
		else if (value == 3)// < << <<<　ここは完成
		{
//			i = check_less_word(&line[i], &flag, status);
			while (analysis_char(line[i]) == value)
			{
				ft_printf("%c", line[i]);
				i++;
			}
			if (2 < i || (flag & NEED_FILE))
			{
				ft_putendl_fd(" : syntax error near unexpected token `<'", 1);
				flag += ERROR;
			}
			else if (i == 2)
			{
				ft_putendl_fd(" : heredoc", 1);
				flag = flag | HEREDOC;
			}
			else if (i == 1)
			{
				ft_putendl_fd(" : redirect", 1);
				flag = flag | INPUT_REDIRECT;
			}
		}
		else if (value == 4)// > >> >> ここは完成
		{
//			i = check_more_word(&line[i], &flag, status);
			while (analysis_char(line[i]) == value)
			{
				ft_printf("%c", line[i]);
				i++;
			}
			if (2 < i || (flag & NEED_FILE))
			{
				ft_putendl_fd(" : syntax error near unexpected token `>'", 1);
				flag += ERROR;
			}
			else if (i == 2)
			{
				ft_putendl_fd(" : re:heredoc", 1);
				flag = flag | APPENDDOC;
			}
			else if (i == 1)
			{
				ft_putendl_fd(" : re:redirect", 1);
				flag = flag | OUTPUT_REDIRECT;
			}
		}
		else if (value == 6)// |
		{
//			i = check_pipe_word(&line[i], &flag, status);
			while (analysis_char(line[i]) == value)
			{
				ft_printf("%c", line[i]);
				i++;
			}
			if (1 < i || (flag & NEED_FILE) || !(flag & COMMAND))
			{
				ft_putendl_fd(" : syntax error near unexpected token `|'", 1);
				flag += ERROR;
			}
			else if (i == 1)
			{
				ft_putendl_fd(" : pipe", 1);
				flag = AT_PIPE;
			}
		}
		else
		{
			ft_printf("%c : else\n", *line);
			line++;
		}
		line += i;
	}
	lexar_panda_error_check(&flag, status);//errorチェック
	(void)status;
	(void)i;
	ft_printf("\n%u\n",flag);
}
