/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 20:09:48 by tokazaki          #+#    #+#             */
/*   Updated: 2023/09/05 16:58:54 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "pipex.h"
// # include "builtin.h"
// # include "lexar_panda.h"
# include <stdio.h>
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

# define INPUT_REDIRECT 0x010
# define HEREDOC 0x020
# define OUTPUT_REDIRECT 0x040
# define APPENDDOC 0x080
# define NEED_FILE INPUT_REDIRECT + HEREDOC + OUTPUT_REDIRECT + APPENDDOC

# define ERROR 0x200
# define NOFLAG 0x400
//

typedef struct s_list
{
	char				*content;
	struct s_list		*next;
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
	t_list			*env; //exportの中身をpush_backする, unsetで消す
	t_libft_list	*line;
	struct s_stack	*stack;
}	t_info;

void	check_line(char *line, t_info *status);

//list.c
t_list	*create_list(char *str);
void	push_back(t_list **head, char *str);
void	free_list(t_list *head);
void	free_stack(t_info *status);

void	add_sigaction(void);
void	line_read(void);

//lexar.c
void	panda(char *line, t_info *status);
void	make_env_list(t_info *status, char *env[]);
char	*serch_env(t_info *status, char *str);

//getpath.c
char	*check_access(char *command, t_info *status);


void	ex_heredoc(char *line);
void	ex_env(void);
void	ex_unset(char **split);
void	ex_export(t_info *status, t_stack *data);
void	ex_echo(t_info *status, t_stack *data);
void	ex_cd(t_info *status, t_stack *data);
void	ex_pwd(void);
void	ex_execve(char **command, int pipe_flag, t_info *status);
void	ex_exit(int i);


void	debug(t_info *status,char *str);
#endif
