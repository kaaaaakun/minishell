/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexar_panda.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 17:48:21 by tokazaki          #+#    #+#             */
/*   Updated: 2023/08/27 18:34:59 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	analysis_char(char c)
{
	if (ft_isdigit(c) || ft_isalpha(c) || c =='-' || c =='_')
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

void	lekpan(char *line, t_info *status)
{
	int	s_quote_f;
	int	w_quote_f;
	int	i;
	int	value;
	int	flag;
	int	heredoc;
	int	command;

	s_quote_f = 0;
	w_quote_f = 0;
	flag = 0;
	command = 0;
	heredoc = 0;
	if (*line == '\0')
		return ;
	while(*line != '\0')
	{
		i = 0;
		value = -1;
		value = analysis_char(*line);
		if (value == 1)// noflags
		{
			while (analysis_char(line[i]) == value)
			{
				ft_printf("%c", line[i]);
				i++;
			}
				if (heredoc == 1)
				{
					heredoc = 0;
					ft_putendl_fd(" : heredoc EOF", 1);
				}
				else if (command == 0)
				{
					ft_putendl_fd(" : command", 1);
					command = 1;
				}
				else
					ft_putendl_fd(" : flag or file", 1);
			flag = 0;
		}
		else if (value == 2)// ' '
		{
			while (analysis_char(line[i]) == value)
			{
				i++;
			}
		}
		else if (value == 3)// < << <<<
		{
			while (analysis_char(line[i]) == value)
		{
				ft_printf("%c", line[i]);
				i++;
			}
			if (2 < i || flag)
				ft_putendl_fd(" : syntax error near unexpected token `<'", 1);
			else if (i == 2)
			{
				ft_putendl_fd(" : heredoc", 1);
				flag = 1;
				heredoc = 1;
			}
			else if (i == 1)
			{
				ft_putendl_fd(" : redirect", 1);
				flag = 1;
			}
		}
		else if (value == 4)// > >> >>>
		{
			while (analysis_char(line[i]) == value)
			{
				ft_printf("%c", line[i]);
				i++;
			}
			if (2 < i || flag)
				ft_putendl_fd(" : syntax error near unexpected token `>'", 1);
			else if (i == 2)
			{
				ft_putendl_fd(" : re:heredoc", 1);
				flag = 1;
			}
			else if (i == 1)
			{
				ft_putendl_fd(" : re:redirect", 1);
				flag = 1;
			}
		}
		else if (value == 5)// $
		{
			i++;
			if (line[i] == '\0' || line[i] == ' ')
			{
				ft_printf("$ : only\n");
				i++;
			}
			else if (line[i] == '$')
			{
				ft_printf("$$ : PID\n");
				i++;
			}
			else
			{
				while (line[i] != '\0' && line[i] != ' ' && line[i] != '<'  && line[i] != '>' && line[i] != '|' && line[i] != '$')
				{
					ft_printf("%c", line[i]);
					i++;
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
			if (1 < i || command == 0)
			{
				ft_putendl_fd(" : syntax error near unexpected token `|'", 1);
			}
			else if (i == 1)
			{
				ft_putendl_fd(" : pipe", 1);
				flag = 1;
				command = 0;
			}
		}
		else if (value == 7)// "
		{
			w_quote_f = 1;
			i++;
//			i = in_double_quote(&line[i], &flag, status);
			while (line[i] != '\"' && line[i] != '\0')
			{
				ft_printf("%c", line[i]);
				i++;
			}
			if (heredoc == 1)
			{
				heredoc = 0;
				ft_putendl_fd(" : heredoc EOF", 1);
			}
			else if (command == 0)
			{
				ft_putendl_fd(" : command", 1);
				command = 1;
			}
			else
				ft_putendl_fd(" : flag or file", 1);
			if (line[i] == '\"')
			{
				w_quote_f = 0;
				i++;
			}
			flag = 0;
		}
		else if (value == 8)// '
		{
			s_quote_f = 1;
			i++;
//			i = in_single_quote(&line[i], &flag, status);
			while (line[i] != '\'' && line[i] != '\0')
			{
				ft_printf("%c", line[i]);
				i++;
			}
			if (heredoc == 1)
			{
				heredoc = 0;
				ft_putendl_fd(" : heredoc EOF", 1);
			}
			else if (command == 0)
			{
				ft_putendl_fd(" : command", 1);
				command = 1;
			}
			else
				ft_putendl_fd(" : flag or file", 1);
			if (line[i] == '\'')
			{
				s_quote_f = 0;
				i++;
			}
			flag = 0;
		}
		else
		{
			ft_printf("%c : else\n", *line);
			line++;
		}
		line += i;
	}
	if (w_quote_f == 1)
				ft_putendl_fd(" \"syntax error `\"'", 1);
	if (s_quote_f == 1)
				ft_putendl_fd(" \"syntax error `\''", 1);
	if (flag == 1)
				ft_putendl_fd(" \"syntax error `< << | > >>'", 1);
	if (command == 0)
				ft_putendl_fd(" \"syntax error `|'", 1);
	(void)status;
	(void)i;
}
