/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:28:35 by tokazaki          #+#    #+#             */
/*   Updated: 2023/09/30 13:29:55 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_panda.h"
#include "minishell.h"
#include <errno.h>

char	*make_tmp_file(t_info *status, int *tmp_fd)
{
	int		nbr;
	char	*char_nbr;
	char	*origin_file_name;
	char	*tmp_file_name;

	*tmp_fd = 0;
	nbr = 0;
	origin_file_name = ft_strdup("/tmp/.tmp");
	tmp_file_name = origin_file_name;
	*tmp_fd = open(tmp_file_name, O_APPEND | O_RDWR, 0);
	d_printf("[%d]",*tmp_fd);
	while (*tmp_fd != -1 && errno != ENOENT && nbr < 5000)
	{
		char_nbr = ft_itoa(nbr);
		tmp_file_name = ft_strjoin_free(origin_file_name, char_nbr, SECOND_FREE);
		*tmp_fd = open(tmp_file_name, O_APPEND | O_RDWR, 0);
		nbr++;
	}
	free(origin_file_name);
	//*tmp_fd がファイルが存在しないので開けない場合
	//ファイルをtmpファイルを作成する
	*tmp_fd = open_ee(status, tmp_file_name, O_CREAT | O_APPEND | O_RDWR, \
		S_IRWXU | S_IRGRP| S_IROTH);
	if (*tmp_fd < 0)
		return (NULL);
	return (tmp_file_name);
	(void)status;
}

char	*check_command_path(t_info *status, char *result)
{
	char	*path;
	char	**splited_path;

	path = search_env(status, "PATH");
	splited_path = ft_split(path, ':');
	path = check_path(result, splited_path);
	return (path);
	(void)result;
	(void)status;
}

char	*check_flag(t_info *status, char *result, int *flag)
{
//	return ;//ここで一回止めてる
	d_printf("[check_flag]");
	if (*flag & INPUT_REDIRECT)
		check_infile(status, result);
	else if (*flag & OUTPUT_REDIRECT)
		check_outfile(status, result);
	else if (*flag & HEREDOC)
	{
		result = (check_heredoc(status, result));
	}
	else if (*flag & APPENDDOC)
		check_appendfile(status, result);
	else if (!(*flag & COMMAND))
	{
	//	data->content = check_command_path(status, ft_strjoin("/", result));
		check_command_path(status, ft_strjoin("/", result));
	}
	d_printf("\n[[%s]]", result);
	return (result);
}

int	search_dollar(char *line)
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
			d_printf("$ : $ only\n");
			i++;
		}
		else if (line[i] == '$')
		{
			d_printf("$$ : PID\n");
			i++;
		}

	}
}

char	*make_list(int *flag, char *line, int len, t_list **list)
{
	char	*result;

//	len = search_dollar(line);
	result = ft_substr(line, 0, len);
	if (!result)
	{
//		status->error == 1;
		return (NULL);
	}
	push_back(list, result);
	return (result);
	(void)flag;
}
