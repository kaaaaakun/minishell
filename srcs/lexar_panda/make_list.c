/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:28:35 by tokazaki          #+#    #+#             */
/*   Updated: 2023/09/07 16:07:01 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexar_panda.h"
#include "minishell.h"
#include <errno.h>

void	check_infile(t_info *status, char *result)
{
	int fd;

	fd = open_ee(result, O_RDONLY, 0);
	if (fd < 0)
		return ;
	dup2_ee(fd, STDIN_FILENO);
	close_ee(fd);
	(void)status;
}


char	*make_tmp_file(t_info *status, int *tmp_fd)
{
	int		nbr;
	char	*char_nbr;
	char	*origin_file_name;
	char	*tmp_file_name;

	*tmp_fd = 0;
	nbr = 0;
	origin_file_name = ft_strdup(".tmp");
	tmp_file_name = origin_file_name;
	*tmp_fd = open(tmp_file_name, O_APPEND | O_RDWR, 0);
	ft_printf("[%d]",*tmp_fd);
	while (*tmp_fd != -1 && errno != ENOENT && nbr < 5000)
	{
		char_nbr = ft_itoa(nbr);
		tmp_file_name = ft_strjoin(origin_file_name, char_nbr);
		*tmp_fd = open(tmp_file_name, O_APPEND | O_RDWR, 0);
		nbr++;
	}
	//*tmp_fd がファイルが存在しないので開けない場合
	//ファイルをtmpファイルを作成する
	*tmp_fd = open_ee(tmp_file_name, O_CREAT | O_APPEND | O_RDWR, \
		S_IRWXU | S_IRGRP| S_IROTH);
	if (*tmp_fd < 0)
		return (NULL);
	return (tmp_file_name);
	(void)status;
}

void	ex_heredoc(t_info *status, char *eof_word, int tmp_fd)
{
	char	*line;
	int		eof_len;

	eof_len = ft_strlen(eof_word) + 1;
	while (1)
	{
		line = readline(">");
		if (line == NULL || ft_strncmp(line, eof_word, eof_len) == 0)
			break ;
		ft_putendl_fd(line, tmp_fd);
		free(line);
	}
	(void)status;
}

void	check_heredoc(t_info *status, char *eof_word)
{
	char	*tmp_file_name;
	int		tmp_fd;

	tmp_file_name = make_tmp_file(status, &tmp_fd);
	ex_heredoc(status, eof_word, tmp_fd);
	check_infile(status, tmp_file_name);
	(void)status;
}

void	check_outfile(t_info *status, char *result)
{
	int fd;

	fd = open_ee(result, O_CREAT | O_TRUNC | O_WRONLY, \
		S_IRWXU | S_IRGRP| S_IROTH);
	dup2_ee(fd, STDOUT_FILENO);
	close_ee(fd);
	(void)status;
}

void	check_appendfile(t_info *status, char *result)
{
	int fd;

	fd = open_ee(result, O_CREAT | O_APPEND | O_WRONLY, \
		S_IRWXU | S_IRGRP| S_IROTH);
	dup2_ee(fd, STDOUT_FILENO);
	close_ee(fd);
	(void)status;
}

char	*check_command_path(t_info *status, char *result)
{
	char	*path;
	char	**splited_path;

	path = serch_env(status, "PATH");
	splited_path = ft_split(path, ':');
	path = check_path(result, splited_path);
	return (path);
	(void)result;
	(void)status;
}

void	check_flag(t_info *status, char *result, int *flag)
{
//	return ;//ここで一回止めてる
	ft_printf("[check_flag]");
	if (*flag & INPUT_REDIRECT)
		check_infile(status, result);
	else if (*flag & OUTPUT_REDIRECT)
		check_outfile(status, result);
	else if (*flag & HEREDOC)
		check_heredoc(status, result);
	else if (*flag & APPENDDOC)
		check_appendfile(status, result);
	else if (!(*flag & COMMAND))
	{
	//	data->content = check_command_path(status, ft_strjoin("/", result));
		check_command_path(status, ft_strjoin("/", result));
	}
}

void	*mini_memcpy(void *dst, const void *src, size_t n)
{
	char		*d;
	const char	*s;
	int			flag;

	flag = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	d = dst;
	s = src;
	while (n--)
	{
		if ((*s == '\'' || *s == '\"') && !(flag & IN_QUOTE))
		{
			if (*s == '\'')
				flag += S_QUOTE;
			else if (*s == '\"')
				flag += D_QUOTE;
			s++;
		}
		if ((*s == '\'' && flag & S_QUOTE) || (*s == '\"' && flag & D_QUOTE))
		{
			if (*s == '\'')
				flag -= S_QUOTE;
			else if (*s == '\"')
				flag -= D_QUOTE;
			s++;
		}
		*d++ = *s++;
	}
	return (dst);
}

int	serch_dollar(char *line)
{
	int	i;

	i = 0;
	while (1)
	{
		while (line[i] != '$')
		{
			if (line[i] == '\0')
				return (i) ;
			i++;
		}
		i++;
		if (line[i] == '\0' || line[i] == ' ')
		{
			ft_printf("$ : $ only\n");
			i++;
		}
		else if (line[i] == '$')
		{
			ft_printf("$$ : PID\n");
			i++;
		}

	}
}

char	*mini_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	length;
	char			*result;
	char			*str;

	str = (char *)s;
	if (s == NULL)
		return (NULL);
	length = ft_strlen((char *)s);
	if (len == 0 || length <= start)
		return (ft_strdup (""));
	length = ft_strlen(&str[start]);
	if (len < length)
		length = len;
	result = (char *)ft_calloc(length + 1, sizeof(char));
	if (result == NULL)
		return (NULL);
	return (mini_memcpy(result, &str[start], length));
}

char	*make_list(int *flag, char *line, int len, t_list **list)
{
	char	*result;

//	len = serch_dollar(line);
	result = mini_substr(line, 0, len);
	if (!result)
	{
//		status->error == 1;
		return (NULL);
	}
	push_back(list, result);
	return (result);
	(void)flag;
}
