/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 20:09:48 by tokazaki          #+#    #+#             */
/*   Updated: 2023/09/07 14:38:56 by tokazaki         ###   ########.fr       */
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

# include "typedef_struct.h"

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

//debug.c
void	debug(t_info *status,char *str);
void	debug_env(t_info *status,char *str);
#endif
