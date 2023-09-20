/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_panda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 17:48:21 by tokazaki          #+#    #+#             */
/*   Updated: 2023/09/20 14:59:55 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"
#include "lexer_panda.h"

//未対応
//1,環境変数内に""がある場合
//$ export a='"aaa"'
//$ "$a"
//

void	check_command(t_info *status, t_stack *data);
void	plusle_quote(char s, int *flag);
void	minun_quote(char s, int *flag);

int	analysis_char(char c)
{
	if (ft_isdigit(c) || ft_isalpha(c) || c =='-' || c =='\"' || c =='\'' || c =='/' || c =='$' || c =='.'|| c =='+' || c =='_')
		return (1);
	if (c == ' ')
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

void	search_env_variable(char *line, int *i, int *flag)
{
	d_printf("[search_env_variable]");
	while ((line[*i] != '$' || *flag & S_QUOTE) && line[*i] != '\0')
	{
		d_printf("\n%c",line[*i]);
		if ((line[*i] == '\'' || line[*i] == '\"') && !(*flag & IN_QUOTE))
		{
			plusle_quote(line[*i], flag);
			*i += 1;
		}
		else if ((line[*i] == '\'' && *flag & S_QUOTE) || (line[*i] == '\"' && *flag & D_QUOTE))
		{
			minun_quote(line[*i], flag);
			*i += 1;
		}
		else if (line[*i] == '<' && line[*i + 1] == '<' && !(*flag & IN_QUOTE))
		{
			*flag += HEREDOC;
			*i += 2;
			while (analysis_char(line[*i]) == 2)
				*i += 1;
			while (analysis_char(line[*i]) == 1)
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
	char	*exit_nbr;

	
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
	else if (line[*i] == '$' && line[*i + 1] == '?')
	{
		exit_nbr = ft_itoa(status->exit_status);
		result = ft_strjoin(result, exit_nbr);
		*i += 2;
	}
	return (result);
	(void)status;
}

char	*search_and_append_env(t_info *status, char *result, char *post_word, int *flag)
{
	d_printf("[s_a_ap_env]\n");
	int	i;
	int	j;
	char	*space_splited_word;

	i = 0;
	j = 0;
	post_word = search_env(status, post_word);
	if (post_word != NULL)
	{
		if (*flag & D_QUOTE)
		{
//			char *dquote = ft_strchr(post_word, '\'');
//			char *squote = ft_strchr(post_word, '\"');
//		d_printf("[d:%s s:%s]\n",dquote,squote);
//			if (dquote == NULL || (squote < dquote && squote != NULL))
				result = ft_strjoin(result, post_word);
//			else
//			{
//				char *chageptr = ft_strrchr(result, '\"');
//				*chageptr = '\'';
//				result = ft_strjoin(result, post_word);
//			}
		}
		else
		{
			while(post_word[i] == ' ')
				i++;
			while(post_word[i] != '\0')
			{
				while(post_word[i] != '\0' && post_word[i] != ' ')
					i++;
				if (j == 0)
				{
					result = ft_strjoin(result, "\'");
					space_splited_word = ft_substr(post_word, 0, i - j);
					result = ft_strjoin(result, "\'");
				}
				result = ft_strjoin(result, "\'");
				space_splited_word = ft_substr(post_word, j, i - j);
				result = ft_strjoin(result, space_splited_word);
				while(post_word[i] == ' ')
					i++;
				if (post_word[i - 1] == ' ')
					result = ft_strjoin(result, "\' ");
				else
					result = ft_strjoin(result, "\'");
				j = i;
			}
		}
	}
	d_printf("[result:%s]\n",result);
	return (result);
}

char	*process_dollar(t_info *status, char *result, int *i, int *flag)
{
	char	*pre_word;
	char	*line;
	int		k;

	line = status->line;
	if (*flag & HEREDOC)
	{
		k = find_next_token(line, *i, *flag);
		pre_word = ft_substr(&line[*i], 0, k);
	}
	else if (line[*i] == '$' && (line[*i + 1] == '\0' || line[*i + 1] == ' ' || line[*i + 1] == '$' || line[*i + 1] == '?'))
		result = process_single_double_dollar(status, line, i, result);
	else// if (line[*i] == '$')
	{
		*i += 1;
		k = find_next_token(line, *i, *flag);
		pre_word = ft_substr(&line[*i], 0, k);
		result = search_and_append_env(status, result, pre_word, flag);
		*i += k;
	}
	return (result);
}


int	count_pipe(t_info *status,char *line)
{
	d_printf("[count_pipe]");
	int	count;
	int	flag;
	int	i;

	count = 0;
	flag =0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (flag & IN_QUOTE)
				minun_quote(line[i], &flag);
			if (!(flag & IN_QUOTE))
				plusle_quote(line[i], &flag);
		}
		if (!(flag & IN_QUOTE) && line[i] == '|')
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
	d_printf("[pipe:count:%d]",count);
	return (count);
	(void)status;
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
		search_env_variable(line, &i, &flag);
		if (j == 0)
			result = ft_substr(line, j, i - j);
		else
			result = ft_strjoin(result, ft_substr(line, j, i - j));
		if (line[i] == '$')
			result = process_dollar(status, result, &i, &flag);
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

t_stack	*search_last_stack(t_info *status)//最後のstackを探して返す
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

	data = search_last_stack(status);
	ft_putendl_fd(" : no*flag redirect", 1);
	char *str = make_list(flag, line, j, &data->inputlist);
	check_flag(status, str, flag);
	*flag = *flag - INPUT_REDIRECT;
}

void make_output_redirect(int *flag, char *line, int j, t_info *status)
{
	t_stack	*data;

	data = search_last_stack(status);
	char *str;
	ft_putendl_fd(" : RE redirect", 1);
	str = make_list(flag, line, j, &data->outputlist);
	check_flag(status, str, flag);
	*flag -= OUTPUT_REDIRECT;
}

void	make_heredoc_list(int *flag, char *line, int j, t_info *status)
{
	char	*str;
	t_stack	*data;

	data = search_last_stack(status);
	ft_putendl_fd(" : heredoc", 1);
	str = mini_substr(line, 0, j);
	str = check_flag(status, str, flag);
	push_back(&data->heredoclist, str);
	*flag -= HEREDOC;
}

void make_append_list(int *flag, char *line, int j, t_info *status)
{
	char *str;
	t_stack	*data;

	data = search_last_stack(status);
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

	data = search_last_stack(status);
	str = make_list(flag, line, j, &data->cmdlist);
	check_flag(status, str, flag);
	*flag = *flag | COMMAND;
}

void make_other_list(int *flag, char *line, int j, t_info *status)
{
	char *str;
	t_stack	*data;

	data = search_last_stack(status);
	ft_putendl_fd(" : *flag or file", 1);
	str = make_list(flag, line, j, &data->cmdlist);
	check_flag(status, str, flag);
}

void	check_input_operation(t_info *status, char *line, int j, int *flag)
{
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
	pid_t	pid;
	int		pipefd[2];

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
		if (pipe(pipefd) < 0)
			error_exit("pipe");
		d_printf("do-fork");
		pid = fork();
		if (pid < 0)
			error_exit("fork");
		if (pid == 0)
		{
			dup2_ee(pipefd[1], STDOUT_FILENO);//ここが変になるかも
			close_ee(pipefd[1]);
			close_ee(pipefd[0]);
			status->pid = 1;
			check_command(status, status->stack);
		}
		status->pid = pid;
		dup2_ee(pipefd[0], STDIN_FILENO);//ここが変になるかも
		close_ee(pipefd[1]);
//		close_ee(pipefd[0]); これなくていいんだっけ？
		data = make_stack(status, data);
	}
	return (i);
	(void)status;
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
	if (1 < i || (*flag & NEED_FILE) || !(*flag & COMMAND))
	{
		ft_putendl_fd(" : syntax error near unexpected token `|'", 1);
		*flag += ERROR;
	}
	else if (i == 1)
	{
		ft_putendl_fd(" : pipe", 1);
		*flag = AT_PIPE;
	}
	return (i);
	(void)status;
}

char	*mini_ft_strchr(const char *s, int c)
{
	char	*str;
	char	chr;

	if (!s)
		return (NULL);
	str = (char *)s;
	chr = (char)c;
	while (*str || chr == '\0')
	{

		if (*str == chr)
			return (str);
		str++;
	}
	return (NULL);
}

void	check_error(t_info *status, char *line, int *e_flag)
{
	int	i;
	int	j;
	int	flag;
	int	value;

	flag = 0;
	while(*line != '\0')
	{
		i = 0;
		value = analysis_char(*line);
		if (value == 1 || value == 0)// command系の処理
		{
			j = process_quotes(line, &value, &i, &flag);
			check_input_operation(status, line, j, &flag);
		}
		if (value == 2)// ' '
			i++;
		else if (value == 3 && !(flag & IN_QUOTE))// < << <<<　ここは完成
			i += process_input_redirect_operation(status, line, &flag);
		else if (value == 4 && !(flag & IN_QUOTE))// > >> >> ここは完成
			i += process_output_redirect_operation(status, line, &flag);
		else if (value == 6 && !(flag & IN_QUOTE))// |
			i += check_pipe_operation(status, line, &flag);
		line += i;
	}
	if (flag & NEED_FILE || flag & IN_QUOTE || flag & ERROR)
	{
		if (!(flag & ERROR))
			flag += ERROR;
		d_printf("\n\\\\ERROR!!!!!!!!!!!//\n");
	}
	*e_flag = flag;
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

void	panda(char *line, t_info *status)
{
	d_printf("[panda]");
	t_stack	*data;
	int	flag;
//	int	pipe;

	flag = INITIAL;
	if (*line == '\0')
		return ;
	check_error(status, line, &flag);
	if (flag & ERROR)
	{
		lexer_panda_error_check(&flag, status);//errorチェック
		d_printf("errorだ！おかえり〜\n");
		status->error = -1;
		return ;
	}
	flag = INITIAL;
	d_printf("[panda]");
	data = make_stack(status, NULL);
	status->pipe = check_and_count_pipe(status, line);
	line = check_dollar(status, line);
	d_printf("\n{pipe;%d}\n",status->pipe);
	d_printf("[panda]");
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
	(void)data;
}
