/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexar_panda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 17:48:21 by tokazaki          #+#    #+#             */
/*   Updated: 2023/09/08 16:51:34 by tokazaki         ###   ########.fr       */
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
	if (c == '|')
		return (6);
	return (0);
}

void	serch_env_variable(char *line, int *i, int *flag)
{
	while ((line[*i] != '$' || *flag & S_QUOTE) && line[*i] != '\0')
	{
		ft_printf("\n%c",line[*i]);
		if ((line[*i] == '\'' || line[*i] == '\"') && !(*flag & IN_QUOTE))
		{
			if (line[*i] == '\'')
				*flag += S_QUOTE;
			else if (line[*i] == '\"')
				*flag += D_QUOTE;
			*i += 1;
		}
		else if ((line[*i] == '\'' && *flag & S_QUOTE) || (line[*i] == '\"' && *flag & D_QUOTE))
		{
			if (line[*i] == '\'')
				*flag -= S_QUOTE;
			else if (line[*i] == '\"')
				*flag -= D_QUOTE;
			*i += 1;
		}
		else
			*i += 1;
	}
}

int	find_next_token(char *line, int i, int flag)
{
	int	k;

	k = 0;
	while (line[i + k] != '\"' && line[i + k] != '\0' && line[i + k] != '$' && \
		((line[i + k] != '\'' && line[i + k] != ' ' && line[i + k] != '<' && \
		line[i + k] != '>' && line[i + k] != '|') || (flag & D_QUOTE)))
		k++;
	ft_printf("[find_next_token:%d %c]",k,line[i+k]);
	return (k);
}

char	*process_dollar_symbol(t_info *status, char *line, int *i, char *result)
{
	if (line[*i] == '$' && (line[*i + 1] == '\0' || line[*i + 1] == ' '))
	{
		result = ft_strjoin(result, "$");
		*i += 1;
	}
	else if (line[*i] == '$' && line[*i + 1] == '$')
	{
		result = ft_strjoin(result, "PID");
		*i += 2;
	}
	return (result);
	(void)status;
}

char	serch_and_append_env(t_info *status, char line[i], char result, int *flag)
{
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
	while (line[i] != '\0')
	{
		serch_env_variable(line, &i, &flag);
		
		if (j == 0)
			result = ft_substr(line, j, i - j);
		else
			result = ft_strjoin(result, ft_substr(line, j, i - j));
///////////
		if (line[i] == '$' && (line[i + 1] == '\0' || line[i + 1] == ' ' || line[i + 1] == '$'))
			result = process_dollar_symbol(status, line, &i, result);
////////////
//		if (line[i] == '$' && (line[i + 1] == '\0' || line[i + 1] == ' '))
//		{
//			result = ft_strjoin(result, "$");
//			i++;
//		}
//		else if (line[i] == '$' && line[i + 1] == '$')
//		{
//			result = ft_strjoin(result, "PID");
//			i += 2;
//		}

//		else if (line[i] == '$')
//		{
//			i++;
//			result = serch_and_append_env(status, &line[i], result, &flag);
//		}
		else if (line[i] == '$')
		{
			result = process_dollar_symbol(status, line, &i, result);
	//		process_env_Variable()
			i++;
			char	*pre_word;
			int		k;

			k = find_next_token(line, i, flag);
			pre_word = ft_substr(&line[i], 0, k);
			pre_word = serch_env(status, pre_word);
			if (pre_word != NULL)
			{
				if (flag & D_QUOTE)
					result = ft_strjoin(result, pre_word);
				else
				{
					result = ft_strjoin(result, "\'");
					result = ft_strjoin(result, pre_word);
					result = ft_strjoin(result, "\'");
				}
			}
/////-------////---------------------------
			i += k;
		}
		j = i;
	}
	ft_printf("\n[end dollar :%s]\n", result);
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
	ft_printf("\n[pre dollar :%s]\n", line);
	data = make_stack(status, NULL);
	line = check_dollar(status, line);
	ft_printf("\n[%s]\n", line);
	while(*line != '\0')
	{
		i = 0;
		value = -1;
		value = analysis_char(*line);
		if (value == 1 || value == 0)// noflags
		{
//			i = check_noflag_word(&line[i], &flag, status);
			while ((analysis_char(line[i]) == value || flag & IN_QUOTE) && line[i] != '\0')
			{
				ft_printf("[[%c]]", line[i]);
				if (line[i] == '\'' && flag & S_QUOTE)
				{
					flag-= S_QUOTE;
					i++;
				}
				else if (line[i] == '\"' && flag & D_QUOTE)
				{
					flag -= D_QUOTE;
					i++;
				}
				else if (line[i] == '\'' && !(flag & IN_QUOTE))
				{
					flag += S_QUOTE;
					i++;
				}
				else if (line[i] == '\"' && !(flag & IN_QUOTE))
				{
					flag += D_QUOTE;
					i++;
				}
				else
					i++;
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
				str = mini_substr(line, 0, i);
				str = check_flag(status, str, &flag);
				push_back(&data->appendlist, str);
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
		if (value == 2)// ' '
		{
			while (analysis_char(line[i]) == value)
				i++;
		}
		else if (value == 3 && !(flag & IN_QUOTE))// < << <<<　ここは完成
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
		else if (value == 4 && !(flag & IN_QUOTE))// > >> >> ここは完成
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
		else if (value == 6 && !(flag & IN_QUOTE))// |
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
		line += i;
	}
	lexar_panda_error_check(&flag, status);//errorチェック
	(void)status;
	(void)i;
	ft_printf("\n%u\n",flag);
}
