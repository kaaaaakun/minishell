/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexar_panda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 17:48:21 by tokazaki          #+#    #+#             */
/*   Updated: 2023/08/29 21:29:47 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	analysis_char(char c)
{
	if (ft_isdigit(c) || ft_isalpha(c) || c =='-')
		return (1);
	if (c == ' ')
		return (2);
	if (c == '<')
		return (3);
	if (c == '>')
		return (4);
	if (c == '$')
		return (5);
	if (c == '|')
		return (6);
	if (c == '\"')
		return (7);
	if (c == '\'')
		return (8);
	if (c == ';')
		return (10);
	return(0);
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

//int	in_double_quote(char *line, int *flag, t_info *status)
//{
//	int	i = 0;
//
//	while (line[i] != '\"' && line[i] != '\0')
//	{
//		ft_printf("%c", line[i]);
//		i++;
//	}
//	if (heredoc == 1)
//	{
//		heredoc = 0;
//		ft_putendl_fd(" : heredoc EOF", 1);
//	}
//	else if (command == 0)
//	{
//		ft_putendl_fd(" : command", 1);
//		command = 1;
//	}
//	else
//		ft_putendl_fd(" : flag or file", 1);
//	if (line[i] == '\"')
//	{
//		w_quote_f = 0;
//		i++;
//	}
//	flag = 0;
//	(void)status;
//	return (i);
//}
//int	in_single_quote(char *line, int *flag, t_info *status)
//{
//	int	i = 0;
//
//	while (line[i] != '\"' && line[i] != '\0')
//	{
//		ft_printf("%c", line[i]);
//		i++;
//	}
//	if (heredoc == 1)
//	{
//		heredoc = 0;
//		ft_putendl_fd(" : heredoc EOF", 1);
//	}
//	else if (command == 0)
//	{
//		ft_putendl_fd(" : command", 1);
//		command = 1;
//	}
//	else
//		ft_putendl_fd(" : flag or file", 1);
//	if (line[i] == '\"')
//	{
//		w_quote_f = 0;
//		i++;
//	}
//	flag = 0;
//	(void)status;
//	return (i);
//}
void	lekar(char *line, t_info *status)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i] != ' ')
		line++;
	while (line[i] != '\0')
	{
		while (line[i] != '\0' && line[i] != ' ' && line[i] != '<'  && line[i] != '>' && line[i] != '|' && line[i] != '$')
			i++;

		while (line[i] != '\0' && line[i] != ' ')
			line++;
	}
	(void)line;
	(void)status;
}

void	make_list(char *line, int len, t_list *list)
{
	ft_printf("[make list]");
	char	*result;

	result = ft_substr(line, 0, len);
	if (!result)
	{
//		info->error == 1;
		return ;
	}
	push_back(&list, result);
}

char	*serch_env(t_info *status, char *str)
{
	ft_printf("[serch_env]");
	t_list	*env;
	char	*serched_word;
	int		len;

	env = status->env;
	serched_word = ft_strjoin(str, "=");
	//status->error
	len = ft_strlen(serched_word);
	ft_printf("[%s:%d]",serched_word,len);
	while (env->next != NULL)
	{
		if (ft_strncmp(env->content, serched_word, len) == 0)
			break ;
		env = env->next;
	}
	if (ft_strncmp(env->content, serched_word, len) != 0)
		return (NULL);
	return (&env->content[len]);

}

void	panda(char *line, t_info *status)
{
	ft_printf("[panda]");
	int	i;
	int	value;
	int	flag;

	flag = INITIAL;
	if (*line == '\0')
		return ;
	while(*line != '\0')
	{
		i = 0;
		value = -1;
		value = analysis_char(*line);
		ft_printf("[panda:%c:%d]",*line,value);
		if (value == 1) // noflags
		{
				while (analysis_char(line[i]) == value)
				{
					ft_printf("%c", line[i]);
					i++;
				}
				if (flag & REDIRECT)
				{
					flag = flag - REDIRECT;
					ft_putendl_fd(" : redirect", 1);
					//make_list(line, i, status->inputlist);
				}
				else if (flag & RE_REDIRECT)
				{
					flag -= RE_REDIRECT;
					ft_putendl_fd(" : RE redirect", 1);
					//make_list(line, i, status->oututlist);
				}
				else if (flag & HEREDOC)
				{
					flag -= HEREDOC;
					ft_putendl_fd(" : heredoc", 1);
					//make_list(line, i, status->heredoclist);
				}
				else if (flag & RE_HEREDOC)
				{
					flag -= RE_HEREDOC;
					ft_putendl_fd(" : re_heredoc", 1);
					//make_list(line, i, status->appendlist);
				}
				else if (!(flag & COMMAND))
				{
					ft_putendl_fd(" : command", 1);
					flag = flag | COMMAND;
					//make_list(line, i, status->heredoclist);
				}
				else
					ft_putendl_fd(" : flag or file", 1);
					//make_list(line, i, status->cmdlist);
		}
		else if (value == 2)// ' '
		{
			while (analysis_char(line[i]) == value)
				i++;
		}
		else if (value == 3)// < << <<<
		{
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
				flag = flag | REDIRECT;
			}
		}
		else if (value == 4)// > >> >>>
		{
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
				flag = flag | RE_HEREDOC;
			}
			else if (i == 1)
			{
				ft_putendl_fd(" : re:redirect", 1);
				flag = flag | REDIRECT;
			}
		}
		else if (value == 5)// $
		{
			line++;
			if (line[i] == '\0' || line[i] == ' ')
			{
				ft_printf("$ : $ only\n");
				//make_list("$", 1, status->cmdlist);
				i++;
			}
			else if (line[i] == '$')
			{
				ft_printf("$$ : PID\n");
				//make_list("$$", 2, status->cmdlist);
				i++;
			}
			else
			{
				while (line[i] != '\0' && line[i] != ' ' && line[i] != '<'  && line[i] != '>' && line[i] != '|' && line[i] != '$')
				{
					ft_printf("%c", line[i]);
					i++;
				}
				char *serch_word = ft_substr(line, 0, i);
				serch_word = serch_env(status, serch_word);
				ft_printf("[%s]\n", serch_word);
				int j = 0;
				while (1)
				{
					while (serch_word[j] == ' ')
						serch_word++;
//					i = in_single_quote(&serch_word[i], &flag, status);
					while (serch_word[j] != ' ' && serch_word[j] != '\'' && serch_word[j] != '\0')
					{
						ft_printf("%c", serch_word[j]);
						j++;
					}
					if (flag & REDIRECT)
					{
						flag = flag - REDIRECT;
						ft_putendl_fd(" : S redirect", 1);
					}
					else if (flag & RE_REDIRECT)
					{
						flag -= RE_REDIRECT;
						ft_putendl_fd(" : S RE redirect", 1);
					}
					else if (flag & HEREDOC)
					{
						flag -= HEREDOC;
						ft_putendl_fd(" : S heredoc", 1);
					}
					else if (flag & RE_HEREDOC)
					{
						flag -= RE_HEREDOC;
						ft_putendl_fd(" : S re_heredoc", 1);
					}
					else if (!(flag & COMMAND))
					{
						ft_putendl_fd(" : S command", 1);
						flag = flag | COMMAND;
					}
					else if (flag & COMMAND)
						ft_putendl_fd(" : S flag or file", 1);
					if (serch_word[j] == '\0')
						break ;
					serch_word += j;
				}
				ft_printf(" : env\n");
			}
		}
		else if (value == 6)// |
		{
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
		else if (value == 7)// "
		{
			flag += D_QUOTE;
			i++;
//			i = in_double_quote(&line[i], &flag, status);
			while(1)
			{
				while (line[i] != '$' && line[i] != '\"' && line[i] != '\0')
				{
					ft_printf("%c", line[i]);
					i++;
				}
				if (line[i] == '$')
				{
					ft_putendl_fd(" : $展開", 1);
				}
				else if (flag & REDIRECT)
				{
					flag = flag - REDIRECT;
					ft_putendl_fd(" : Dquote redirect", 1);
				}
				else if (flag & RE_REDIRECT)
				{
					flag -= RE_REDIRECT;
					ft_putendl_fd(" : Dquote RE redirect", 1);
				}
				else if (flag & HEREDOC)
				{
					flag -= HEREDOC;
					ft_putendl_fd(" : Dquote heredoc", 1);
				}
				else if (flag & RE_HEREDOC)
				{
					flag -= RE_HEREDOC;
					ft_putendl_fd(" : Dquote re_heredoc", 1);
				}
				else if (!(flag & COMMAND))
				{
					ft_putendl_fd(" : Dquote command", 1);
					flag = flag | COMMAND;
				}
				else if (flag & COMMAND)
					ft_putendl_fd(" : Dquote flag or file", 1);
				if (line[i] == '\"')
				{
					flag -= D_QUOTE;
					i++;
					break ;
				}
				else if (line[i] == '\0')
					break ;
			}
		}
		else if (value == 8)// '
		{
			flag += S_QUOTE;
			i++;
//				i = in_single_quote(&line[i], &flag, status);
				while (line[i] != '\'' && line[i] != '\0')
				{
					ft_printf("%c", line[i]);
					i++;
				}
				if (flag & REDIRECT)
				{
					flag = flag - REDIRECT;
					ft_putendl_fd(" : S redirect", 1);
				}
				else if (flag & RE_REDIRECT)
				{
					flag -= RE_REDIRECT;
					ft_putendl_fd(" : S RE redirect", 1);
				}
				else if (flag & HEREDOC)
				{
					flag -= HEREDOC;
					ft_putendl_fd(" : S heredoc", 1);
				}
				else if (flag & RE_HEREDOC)
				{
					flag -= RE_HEREDOC;
					ft_putendl_fd(" : S re_heredoc", 1);
				}
				else if (!(flag & COMMAND))
				{
					ft_putendl_fd(" : S command", 1);
					flag = flag | COMMAND;
				}
				else if (flag & COMMAND)
					ft_putendl_fd(" : S flag or file", 1);
				if (line[i] == '\'')
				{
					flag -= S_QUOTE;
					i++;
					break ;
				}
				else if (line[i] == '\0')
					break ;
		}
		else
		{
			ft_printf("%c : else\n", *line);
			line++;
		}
		line += i;
	}
	if (flag & D_QUOTE)
				ft_putendl_fd(" \"syntax error `\"'", 1);
	if (flag & S_QUOTE)
				ft_putendl_fd(" \"syntax error `\''", 1);
	if (flag & NEED_FILE)
				ft_putendl_fd(" \"syntax error `< << > >>'", 1);
	if (!(flag = COMMAND))
				ft_putendl_fd(" \"syntax error `|'", 1);
	(void)status;
	(void)i;
	ft_printf("\n%u\n",flag);
}
