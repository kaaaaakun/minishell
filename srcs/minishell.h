/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 20:09:48 by tokazaki          #+#    #+#             */
/*   Updated: 2023/08/22 17:16:38 by tokazaki         ###   ########.fr       */
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

typedef struct s_info {
	int pid;
}	t_info;

void	check_command(char *line, int pipe_flag, t_info *status);
void	check_line(char *line);
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
