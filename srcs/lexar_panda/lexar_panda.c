/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexar_panda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 17:48:21 by tokazaki          #+#    #+#             */
/*   Updated: 2023/09/10 17:37:20 by tokazaki         ###   ########.fr       */
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
		d_printf("\n%c",line[*i]);
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
	d_printf("[find_next_token:%d %c]",k,line[i+k]);
	return (k);
}

char	*process_single_double_dollar(t_info *status, char *line, int *i, char *result)
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

char	*serch_and_append_env(t_info *status, char *result, char *pre_word, int *flag)
{	
	pre_word = serch_env(status, pre_word);
	if (pre_word != NULL)
	{
		if (*flag & D_QUOTE)
			result = ft_strjoin(result, pre_word);
		else
		{
			result = ft_strjoin(result, "\'");
			result = ft_strjoin(result, pre_word);
			result = ft_strjoin(result, "\'");
		}
	}
	return (result);
}

char	*prosess_dollar(t_info *status, char *result, int *i, int *flag)
{
	char	*pre_word;
	char	*line;
	int		k;

	line = status->line;
	if (line[*i] == '$' && (line[*i + 1] == '\0' || line[*i + 1] == ' ' || line[*i + 1] == '$'))
		result = process_single_double_dollar(status, line, i, result);
	else// if (line[*i] == '$')
	{
		*i += 1;
		k = find_next_token(line, *i, *flag);
		pre_word = ft_substr(&line[*i], 0, k);
		result = serch_and_append_env(status, result, pre_word, flag);
		*i += k;
	}
//	d_printf("\n[%s]\n",result);
	return (result);
}

char	*check_dollar(t_info *status, char *line)
{
	d_printf("[check_dollar]");
	int	i;
	int	flag;
	int	j;
	char	*result;

	status->line = line;
	i = 0;
	j = 0;
	flag = 0;
//	result = line;
	while (line[i] != '\0')
	{
		serch_env_variable(line, &i, &flag);	
		if (j == 0)
			result = ft_substr(line, j, i - j);
		else
			result = ft_strjoin(result, ft_substr(line, j, i - j));
		if (line[i] == '$')
			result = prosess_dollar(status, result, &i, &flag);
		j = i;
	}
//	d_printf("\n[end dollar :%s]\n", result);
	return (result);
}

int	process_quotes(char *line, int *value, int *i, int *flag)
{
	int	j;

	j = 0;
	while ((analysis_char(line[*i]) == *value || *flag & IN_QUOTE) && line[*i] != '\0')
	{
		if (line[*i] == '\'' && *flag & S_QUOTE)
			*flag-= S_QUOTE;
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

t_stack	*serch_last_stack(t_info *status)//最後のstackを探して返す
{
	t_stack	*data;

	data = status->stack;
	while (data->next != NULL)
		data = data->next;
	return (data);
}

void make_input_redirect(int *flag, char *line, int j, t_info *status)
{
	t_stack	*data;

	data = serch_last_stack(status);
	ft_putendl_fd(" : no*flag redirect", 1);
	char *str = make_list(flag, line, j, &data->inputlist);
	check_flag(status, str, flag);
	*flag = *flag - INPUT_REDIRECT;
}

void make_output_redirect(int *flag, char *line, int j, t_info *status)
{
	t_stack	*data;

	data = serch_last_stack(status);
	char *str;
	ft_putendl_fd(" : RE redirect", 1);
	str = make_list(flag, line, j, &data->outputlist);
	check_flag(status, str, flag);
	*flag -= OUTPUT_REDIRECT;
}

void make_heredoc_list(int *flag, char *line, int j, t_info *status)
{
	char *str;
	t_stack	*data;

	data = serch_last_stack(status);
	ft_putendl_fd(" : heredoc", 1);
	str = make_list(flag, line, j, &data->heredoclist);
	check_flag(status, str, flag);
	*flag -= HEREDOC;
}

void make_append_list(int *flag, char *line, int j, t_info *status)
{
	char *str;
	t_stack	*data;

	data = serch_last_stack(status);
	ft_putendl_fd(" : append", 1);
	str = mini_substr(line, 0, j);
	str = check_flag(status, str, flag);
	push_back(&data->appendlist, str);
	*flag -= APPENDDOC;
}

void make_command_list(int *flag, char *line, int j, t_info *status)
{
	char *str;
	t_stack	*data;

	data = serch_last_stack(status);
	ft_putendl_fd(" : no*flag command", 1);
	str = make_list(flag, line, j, &data->cmdlist);
	check_flag(status, str, flag);
	*flag = *flag | COMMAND;
}

void make_other_list(int *flag, char *line, int j, t_info *status)
{
	char *str;
	t_stack	*data;

	data = serch_last_stack(status);
	ft_putendl_fd(" : *flag or file", 1);
	str = make_list(flag, line, j, &data->cmdlist);
	check_flag(status, str, flag);
}

void	process_input_operation(t_info *status, char *line, int j, int *flag)
{
	if (*flag & INPUT_REDIRECT)
		make_input_redirect(flag, line,  j, status);
	else if (*flag & OUTPUT_REDIRECT)
		make_output_redirect(flag, line,  j, status);
	else if (*flag & HEREDOC)
		make_heredoc_list(flag, line,  j, status);
	else if (*flag & APPENDDOC)
		make_append_list(flag, line,  j, status);
	else if (!(*flag & COMMAND))
		make_command_list(flag, line,  j, status);
	else
		make_other_list(flag, line,  j, status);
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
	if (2 < i || (*flag & NEED_FILE))
	{
		ft_putendl_fd(" : syntax error near unexpected token `<'", 1);
		*flag += ERROR;
	}
	else if (i == 2)
	{
		ft_putendl_fd(" : heredoc", 1);
		*flag = *flag | HEREDOC;
	} else if (i == 1) {
		ft_putendl_fd(" : redirect", 1);
		*flag = *flag | INPUT_REDIRECT;
	}
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
	if (2 < i || (*flag& NEED_FILE))
	{
		ft_putendl_fd(" : syntax error near unexpected token `>'", 1);
		*flag+= ERROR;
	}
	else if (i == 2)
	{
		ft_putendl_fd(" : re:heredoc", 1);
		*flag= *flag| APPENDDOC;
	}
	else if (i == 1)
	{
		ft_putendl_fd(" : re:redirect", 1);
		*flag= *flag| OUTPUT_REDIRECT;
	}
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
		ft_putendl_fd(" : syntax error near unexpected token `|'", 1);
		*flag += ERROR;
	}
	else if (i == 1)
	{
		ft_putendl_fd(" : pipe", 1);
		*flag = AT_PIPE;
		data = make_stack(status, data);
	}

	return (i);
	(void)status;
}

void	panda(char *line, t_info *status)
{
	d_printf("[panda]");
	t_stack	*data;
	int	flag;

	flag = INITIAL;
	if (*line == '\0')
		return ;
	data = make_stack(status, NULL);
	line = check_dollar(status, line);
	int	i;
	int	j;
	int	value;
	while(*line != '\0')
	{
		i = 0;
		value = analysis_char(*line);
		if (value == 1 || value == 0)// command系の処理
		{
			j = process_quotes(line, &value, &i, &flag);
			process_input_operation(status, line, j, &flag);
		}
		if (value == 2)// ' '
			i++;
		else if (value == 3 && !(flag & IN_QUOTE))// < << <<<　ここは完成
			i += process_input_redirect_operation(status, line, &flag);
		else if (value == 4 && !(flag & IN_QUOTE))// > >> >> ここは完成
			i += process_output_redirect_operation(status, line, &flag);
		else if (value == 6 && !(flag & IN_QUOTE))// |
			i += process_pipe_operation(status, line, &flag);
		line += i;
	}
	lexar_panda_error_check(&flag, status);//errorチェック
}
