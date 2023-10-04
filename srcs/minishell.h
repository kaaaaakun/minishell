/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 20:09:48 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/04 16:22:27 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "pipex.h"
//# include "builtin.h"
// # include "lexer_panda.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <limits.h>

# include "typedef_struct.h"

//global variable
extern int		g_signal;

void	check_line(char *line, t_info *status);

//list.c
t_list	*create_list(char *str);
void	push_back(t_list **head, char *str);
void	free_list(t_list *head);
void	free_stack(t_info *status);
size_t	listsize(t_list *lst);

void	add_sigaction(int i);
void	sighandler_heredoc(int sig);
void	sighandler_sigint(int sig);
void	line_read(void);

//lexer.c
void	panda(char *line, t_info *status);
void	make_env_list(t_info *status, char *env[]);
char	*search_env(t_info *status, char *str);
t_list	*search_envlist(t_info *status, char *str);
t_list	*search_envlist_for_export(t_info *status, char *str);

//getpath.c
char	*check_access(char *command, t_info *status);


//void	ex_heredoc(char *line);
void	ex_execve(t_info *status);
void	free_null(void *ptr);

//debug.c
void	debug(t_info *status, char *str);
void	debug_env(t_info *status, char *str);

//warap free
# define BOTH_FREE 0
# define FIRST_FREE 1
# define SECOND_FREE 2
# define NEITHER_FREE 3

char	*ft_strjoin_free(char const *s1, char const *s2, int free_flag);
char	*ft_strtrim_free(char const *s1, char const *set, int free_flag);

#endif
