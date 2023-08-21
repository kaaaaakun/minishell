/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 20:09:48 by tokazaki          #+#    #+#             */
/*   Updated: 2023/08/21 16:16:39 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "stdio.h"    
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <limits.h>

void	check_command(char *line);
void	ex_env(char **split);
void	ex_unset(char **split);
void	ex_export(char **split);
void	ex_exit(char **split);
void	ex_echo(char **split);
void	ex_cd(char **split);
void	ex_pwd(void);
void	ex_execve(char **split);
void	add_sigaction(void);
void	line_read(void);
int		main(void);
#endif
