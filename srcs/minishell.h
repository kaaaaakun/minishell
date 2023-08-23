/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 20:09:48 by tokazaki          #+#    #+#             */
/*   Updated: 2023/08/23 19:26:19 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "pipex.h"
# include "stdio.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <limits.h>

typedef struct s_info
{
	int				pid;
	int				exec_count;
	struct s_stack	*stack;
}	t_info;

typedef struct s_stack
{
	struct s_outputlist		*outputlist;	//>
	struct s_appendlist		*appendlist;	//>>
	struct s_inputlist		*inputlist;		//<
	struct s_heredoclist	*heredoclist;	//<<
	struct s_cmdlist		*cmdlist;
	struct s_stack			*next;
}	t_stack;

typedef struct s_outputlist
{
	char					*output;
	struct s_outputlist		*next;
}	t_outputlist;

typedef struct s_appendlist
{
	char					*append;
	struct s_appendlist		*next;
}	t_appendlist;

typedef struct s_inputlist
{
	char					*input;
	struct s_inputlist		*next;
}	t_inputlist;

typedef struct s_heredoclist
{
	char						*heredoc;
	struct s_heredoclist		*next;
}	t_heredoclist;

typedef struct s_cmdlist
{
	char				*cmd;
	struct s_cmdlist	*next;
}	t_cmdlist;


void	check_command(char *line, int pipe_flag, t_info *status);


void	ex_heredoc(char *line);
void	ex_env(char **split);
void	ex_unset(char **split);
void	ex_export(char **split);
void	ex_exit(char **split);
void	ex_echo(char **split);
void	ex_cd(char **split);
void	ex_pwd(void);
void	ex_execve(char **command, int pipe_flag, t_info *status);



void	add_sigaction(void);
void	line_read(void);
int		main(void);
#endif
