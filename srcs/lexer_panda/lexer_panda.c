/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_panda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 17:48:21 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/06 15:25:51 by tokazaki         ###   ########.fr       */
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
char	*ft_strjoin_free(char const *s1, char const *s2, int free_flag);
char	*ft_strtrim_free(char const *s1, char const *set, int free_flag);

char	*ft_strjoin_free(char const *s1, char const *s2, int free_flag)
{
	char	*joined_str;

	joined_str = ft_strjoin(s1, s2);
	if (free_flag == FIRST_FREE || free_flag == BOTH_FREE)
	{
		free((void *)s1);
		s1 = NULL;
	}
	if (free_flag == SECOND_FREE || free_flag == BOTH_FREE)
	{
		free((void *)s2);
		s1 = NULL;
	}
	if (joined_str == NULL)
		exit (1);
	return (joined_str);
	(void)free_flag;
}

char	*ft_strtrim_free(char const *s1, char const *set, int free_flag)
{
	char	*trimed_str;

	trimed_str = ft_strtrim(s1, set);
	if (free_flag == FIRST_FREE || free_flag == BOTH_FREE)
		free((void *)s1);
	if (free_flag == SECOND_FREE || free_flag == BOTH_FREE)
		free((void *)set);
	return (trimed_str);
}

int	analysis_char(char c)
{
	if (ft_isdigit(c) || ft_isalpha(c) || c == '-' || c == '\"' || c == '\'' \
		|| c == '/' || c == '$' || c == '.' || c == '+' || c == '_')
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
	while (analysis_char(line[i + count]) == 1)
		count++;
	return (count);
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

int	find_next_token(char *line, int i, int flag)
{
	int	k;

	k = 0;
	while (line[i + k] != '\'' && line[i + k] != '\"' && \
		line[i + k] != ' ' && line[i + k] != '\0' && line[i + k] != '$' && \
		((line[i + k] != '<' && \
		line[i + k] != '>' && line[i + k] != '|') || (flag & D_QUOTE)))
		k++;
	d_printf("[find_next_token:%d %c]", k, line[i + k]);
	return (k);
}

char	*process_single_dollar_in_d_quote(t_info *status, char *line, int *i, char *result)
{
	result = ft_strjoin_free(result, "$", FIRST_FREE);
	*i += 1;
	return (result);
	(void)status;
	(void)line;
}

char	*process_single_double_dollar(t_info *status, char *line, int *i, char *result)
{
	char	*exit_nbr;

	if (line[*i] == '$' && (line[*i + 1] == '\0' || line[*i + 1] == ' '))
	{
		result = ft_strjoin_free(result, "$", FIRST_FREE);
		*i += 1;
	}
	else if (line[*i] == '$' && line[*i + 1] == '$')
	{
		result = ft_strjoin_free(result, "PID", FIRST_FREE);
		*i += 2;
	}
	else if (line[*i] == '$' && line[*i + 1] == '?')
	{
		exit_nbr = ft_itoa(status->exit_status);
		result = ft_strjoin_free(result, exit_nbr, BOTH_FREE);
		*i += 2;
	}
	return (result);
	(void)status;
}

void	skip_space(char *post_word, int *i)
{
	while (post_word[*i] == ' ')
		i += 1;
}

char	*make_first_space_splited_word(char *result, char *post_word, int i, int j)
{
	char	*space_splited_word;

	result = ft_strjoin_free(result, "\'", FIRST_FREE);
	space_splited_word = ft_substr(post_word, 0, i - j);
	result = ft_strjoin_free(result, "\'", FIRST_FREE);
	return (result);
	(void)space_splited_word;
}

char	*append_non_quote_env(char *result, char *post_word)
{
	int		i;
	int		j;
	char	*space_splited_word;

	i = 0;
	j = 0;
	while (post_word[i] != '\0')
	{
		while (post_word[i] != '\0' && post_word[i] != ' ')
			i++;
		if (j == 0)
			result = make_first_space_splited_word(result, post_word, i, j);
		result = ft_strjoin_free(result, "\'", FIRST_FREE);
		space_splited_word = ft_substr(post_word, j, i - j);
		result = ft_strjoin_free(result, space_splited_word, BOTH_FREE);
		skip_space(post_word, &i);
		if (post_word[i - 1] == ' ')
			result = ft_strjoin_free(result, "\' ", FIRST_FREE);
		else
			result = ft_strjoin_free(result, "\'", FIRST_FREE);
		j = i;
	}
	return (result);
}

char	*search_and_append_env(t_info *status, char *result, char *post_word, int *flag)
{
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
	d_printf("[result:%s]\n", result);
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
	else if (line[*i] == '$' && (line[*i + 1] == '\0' || \
		line[*i + 1] == ' ' || line[*i + 1] == '$' || line[*i + 1] == '?'))
		result = process_single_double_dollar(status, line, i, result);
	else if (line[*i + 1] == '\"' && *flag & D_QUOTE)
		result = process_single_dollar_in_d_quote(status, line, i, result);
	else
	{
		*i += 1;
		k = find_next_token(line, *i, *flag);
		pre_word = ft_substr(&line[*i], 0, k);
		d_printf("\n[process_doll/pre_word:%s]", pre_word);
		result = search_and_append_env(status, result, pre_word, flag);
		*i += k;
	}
	return (result);
}

int	count_pipe(t_info *status,char *line)
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

int	process_quotes(char *line, int *value, int *i, int *flag)
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
		line[j] = line[*i];
	}
	return (j);
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

t_stack	*search_last_stack(t_info *status)
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
	char	*str;

	data = search_last_stack(status);
	d_printf(" : no*flag redirect", 1);
	str = make_list(flag, line, j, &data->inputlist);
	check_flag(status, str, flag);
	*flag = *flag - INPUT_REDIRECT;
}

void make_output_redirect(int *flag, char *line, int j, t_info *status)
{
	t_stack	*data;
	char	*str;

	data = search_last_stack(status);
	d_printf(" : RE redirect", 1);
	str = make_list(flag, line, j, &data->outputlist);
	check_flag(status, str, flag);
	*flag -= OUTPUT_REDIRECT;
}

void	make_heredoc_list(int *flag, char *line, int j, t_info *status)
{
	char	*str;
	t_stack	*data;

	data = search_last_stack(status);
	d_printf(" : heredoc", 1);
	str = mini_substr(line, 0, j);
	str = check_flag(status, str, flag);
	push_back(&data->heredoclist, str);
	*flag -= HEREDOC;
}

void make_append_list(int *flag, char *line, int j, t_info *status)
{
	t_stack	*data;
	char	*str;

	data = search_last_stack(status);
	d_printf(" : append", 1);
	str = mini_substr(line, 0, j);
	str = check_flag(status, str, flag);
	push_back(&data->appendlist, str);
	*flag -= APPENDDOC;
}

void make_command_list(int *flag, char *line, int j, t_info *status)
{
	char	*str;
	t_stack	*data;

	data = search_last_stack(status);
	str = make_list(flag, line, j, &data->cmdlist);
	check_flag(status, str, flag);
	*flag = *flag | COMMAND;
}

void make_other_list(int *flag, char *line, int j, t_info *status)
{
	t_stack	*data;
	char	*str;

	data = search_last_stack(status);
	d_printf(" : *flag or file");
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
	if (*flag & NEED_FILE)
	{
		*flag = ERROR + INPUT_REDIRECT;
	}
	else if (2 < i)
	{
		*flag += ERROR;
		*flag += INPUT_REDIRECT;
	}
	else if (i == 2)
		*flag = *flag | HEREDOC;
	else if (i == 1)
		*flag = *flag | INPUT_REDIRECT;
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
	if (*flag & NEED_FILE)
	{
		*flag = ERROR + OUTPUT_REDIRECT;
	}
	else if (2 < i)
	{
		*flag += ERROR;
		*flag += OUTPUT_REDIRECT;
	}
	else if (i == 2)
		*flag = *flag | APPENDDOC;
	else if (i == 1)
		*flag = *flag | OUTPUT_REDIRECT;
	return (i);
	(void)status;
}

# define PIPE_IN 0
# define PIPE_OUT 1

void close_pipe(t_info *status, int *pipefd)
{
	close_ee(status, pipefd[0]);
	close_ee(status, pipefd[1]);
}

void dup2_close_pipe(t_info *status, int *pipefd, int flag)
{
	if (flag == PIPE_IN)
		dup2_ee(status, pipefd[0], flag);
	else if (flag == PIPE_OUT)
		dup2_ee(status, pipefd[1], flag);
	close_pipe(status, pipefd);
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
		*flag += ERROR;
	}
	else if (i == 1)
	{
		check_command(status, status->stack);
	}
	return (i);
	(void)status;
	(void)data;
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
		*flag += ERROR;
	}
	else if (i == 1)
	{
		d_printf(" : pipe");
		*flag = AT_PIPE;
	}
	return (i);
	(void)status;
	(void)data;
}

char	*mini_ft_strchr(const char *s, int c)
{
	char	*str;
	char	chr;
	int		flag;

	if (!s)
		return (NULL);
	str = (char *)s;
	chr = (char)c;
	flag = INITIAL;
	while (*str || chr == '\0')
	{
		if ((*str == '\'' || *str == '\"') && !(flag & IN_QUOTE))
			plusle_quote(*str, &flag);
		else if ((*str == '\'' && flag & S_QUOTE) || \
			(*str == '\"' && flag & D_QUOTE))
			minun_quote(*str, &flag);
		else if (*str == chr && !(flag & IN_QUOTE))
			return (str);
		str++;
	}
	return (NULL);
}

int	count_other_operation(t_info *status, char *line, int *flag, int value)
{
	int	count;

	count = 0;
	if (value == 3 && !(*flag & IN_QUOTE))
		count += process_input_redirect_operation(status, line, flag);
	else if (value == 4 && !(*flag & IN_QUOTE))
		count += process_output_redirect_operation(status, line, flag);
	else if (value == 6 && !(*flag & IN_QUOTE))
		count += check_pipe_operation(status, line, flag);
	return (count);
}

void	check_error(t_info *status, char *line, int *e_flag)
{
	int	i;
	int	j;
	int	flag;
	int	value;

	flag = INITIAL;
	while (*line != '\0' && !(flag & ERROR))
	{
		d_printf("check_erro line : %s\n", line);
		i = 0;
		value = analysis_char(*line);
		if (value == 1 || value == 0)
		{
			j = skip_count_quotes(line, &value, &i, &flag);
			check_input_operation(status, line, j, &flag);
		}
		else if (value == 2)
			i++;
		else if (!(flag & IN_QUOTE))
		i += count_other_operation(status, line, &flag, value);
		line += i;
	}
	if ((flag & NEED_FILE || flag & IN_QUOTE) && !(flag & ERROR))
			flag += ERROR;
	*e_flag = flag;
}

void	process_input_operation(t_info *status, char *line, int j, int *flag)
{
	if (*flag & INPUT_REDIRECT)
		make_input_redirect(flag, line, j, status);
	else if (*flag & OUTPUT_REDIRECT)
		make_output_redirect(flag, line, j, status);
	else if (*flag & HEREDOC)
		make_heredoc_list(flag, line, j, status);
	else if (*flag & APPENDDOC)
		make_append_list(flag, line, j, status);
	else if (!(*flag & COMMAND))
		make_command_list(flag, line, j, status);
	else
		make_other_list(flag, line, j, status);
}

void	exec_panda(char *line, t_info *status, int flag)
{
	int	i;
	int	j;
	int	value;

	while (*line != '\0')
	{
		i = 0;
		value = analysis_char(*line);
		if (value == 1 || value == 0)
		{
			j = process_quotes(line, &value, &i, &flag);
			process_input_operation(status, line, j, &flag);
		}
		if (value == 2)
			i++;
		else if (value == 3 && !(flag & IN_QUOTE))
			i += process_input_redirect_operation(status, line, &flag);
		else if (value == 4 && !(flag & IN_QUOTE))
			i += process_output_redirect_operation(status, line, &flag);
		else if (value == 6 && !(flag & IN_QUOTE))
			return ;
		line += i;
		if (status->error != 0)
			return ;
	}
}

void	wait_child_process(t_info *status, pid_t pid)
{
	int	process_count;
	int	i;
	int	exit_status;

	process_count = status->pipe + 1;
	i = 0;
	while (i < process_count)
	{
		if (waitpid(-1, &exit_status, 0) == pid)
		{
			if (WIFEXITED(exit_status))
				status->exit_status = WEXITSTATUS(exit_status);
			else if (WIFSIGNALED(exit_status))
				status->exit_status = WTERMSIG(exit_status) + 128;
		}
		i++;
	}
}
pid_t	fork_ee(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		error_exit("fork");
	return (pid);
}

void	some_pipes_exec_panda(t_info *status, char *line, int flag, int i)
{
	int		stdin_fd;
	pid_t	pid;
	int		pipefd[2];

	stdin_fd = dup(STDIN_FILENO);
	while (++i)
	{
		if (pipe(pipefd) < 0)
			error_exit("pipe");
		pid = fork_ee();
		if (pid == 0)
		{
			if (i != status->pipe + 1)
				dup2_close_pipe(status, pipefd, STDOUT_FILENO);
			exec_panda(line, status, flag);
			check_command(status, status->stack);
		}
		line = mini_ft_strchr(line, '|');
		if (line == NULL)
			break ;
		line++;
		dup2_close_pipe(status, pipefd, STDIN_FILENO);
	}
	dup2_ee(status, stdin_fd, STDIN_FILENO);
	wait_child_process(status, pid);
}

void	panda(char *line, t_info *status)
{
	t_stack	*data;
	int		flag;
	int		i;

	i = 0;
	if (*line == '\0')
		return ;
	line = check_dollar(status, line);
	check_error(status, line, &flag);
	if (flag & ERROR)
	{
		lexer_panda_error_check(&flag, status);
		d_printf("syntax error \n");
		status->error = -1;
		free_null(line);
		return ;
	}
	data = make_stack(status, NULL);
	status->pipe = check_and_count_pipe(status, line);
	if (status->pipe == 0)
		exec_panda(line, status, flag);
	else
		some_pipes_exec_panda(status, line, flag, i);
	free(line);
	return ;
}
