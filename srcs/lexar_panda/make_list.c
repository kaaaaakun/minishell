/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:28:35 by tokazaki          #+#    #+#             */
/*   Updated: 2023/09/06 18:51:41 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexar_panda.h"
#include "minishell.h"
#include "pipex.h"
void	check_infile(t_info *status, char *result)
{
	int fd;

	fd = open_ee(result, O_RDONLY, 0);
	dup2_ee(fd, STDIN_FILENO);
	close_ee(fd);
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
	return ;//ここで一回止めてる
	ft_printf("[check_flag]");
	if (*flag & INPUT_REDIRECT)
		check_infile(status, result);
	else if (*flag & OUTPUT_REDIRECT)
		check_outfile(status, result);
	else if (*flag & HEREDOC)
		;
	else if (*flag & APPENDDOC)
		;
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
