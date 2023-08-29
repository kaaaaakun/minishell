/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 20:09:48 by tokazaki          #+#    #+#             */
/*   Updated: 2023/08/28 16:58:39 by tokazaki         ###   ########.fr       */
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

//
# define INITIAL 0x000
# define AT_PIPE 0x001
# define COMMAND 0x002

# define D_QUOTE 0x004
# define S_QUOTE 0x008

# define REDIRECT 0x010
# define HEREDOC 0x020
# define RE_REDIRECT 0x040
# define RE_HEREDOC 0x080
# define NEED_FILE REDIRECT + HEREDOC + RE_REDIRECT + RE_HEREDOC 

# define ERROR 0x200
# define NOFLAG 0x400
//

typedef struct s_list
{
	char				*content;
	struct t_list		*next;
}	t_list;

typedef struct s_stack
{
	struct s_list		*outputlist;	//>
	struct s_list		*appendlist;	//>>
	struct s_list		*inputlist;		//<
	struct s_list		*heredoclist;	//<<
	struct s_list		*cmdlist;
	struct s_stack		*next;
}	t_stack;

typedef struct s_info
{
	int				pid;
	int				error;
	int				exec_count;
	t_libft_list	*env;
	struct s_stack	*stack;
}	t_info;

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

//list.c
t_stack	*create_list(char *str);
void	push_back(t_list **head, char *str);
//pino.c
void	init_stack(t_info *status);

void	add_sigaction(void);
void	line_read(void);

//lexar.c
void	lekpan(char *line, t_info *status);
void	make_env_list(t_info *status, char *env[]);
#endif
