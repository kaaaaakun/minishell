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

void	lekpan(char *line, t_info *status)
{
	int	quote_f;
	int	i;
	int	value;
	int	flag;
	int	heredoc;
	int	command;

	quote_f = 0;
	flag = 0;
	command = 0;
	heredoc = 0;
	while(*line != '\0')
	{
		i = 0;
		value = -1;
		value = analysis_char(*line);
		if (quote_f == 1 || quote_f == 2)// in quote
		{
			while (line[i] != '\"' && line[i] != '\"' && line[i] != '\0')
			{
				ft_printf("%c", line[i]);
				i++;
			}
			if (command == 0)
			{
				ft_putendl_fd(" : command", 1);
				command = 1;
			}
			else if (heredoc == 1)
			{
				heredoc = 0;
				ft_putendl_fd(" : heredoc EOF", 1);
			}
			else
				ft_putendl_fd(" : flag or file", 1);
			if (line[i] == '\'' || line[i] == '\"')
			{
				quote_f = 0;
				i++;
			}
			flag = 0;
		}
		else if (value == 1)// noflags
		{
			while (analysis_char(line[i]) == value)
			{
				ft_printf("%c", line[i]);
				i++;
			}
				if (command == 0)
				{
					ft_putendl_fd(" : command", 1);
					command = 1;
				}
				else if (heredoc == 1)
				{
					heredoc = 0;
					ft_putendl_fd(" : heredoc EOF", 1);
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
		else if (value == 6)// |
		{
			while (analysis_char(line[i]) == value)
			{
				ft_printf("%c", line[i]);
				i++;
			}
			if (1 < i)
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
			quote_f = 1;
			i++;
		}
		else if (value == 8)// '
		{
			quote_f = 2;
			i++;
		}
		else
		{
			ft_printf("%c : else\n", *line);
			line++;
		}
		line += i;
	}
	if (quote_f == 1)
				ft_putendl_fd(" \"syntax error `\"'", 1);
	else if (quote_f == 2)
				ft_putendl_fd(" \"syntax error `\''", 1);
	(void)status;
	(void)i;
}
