/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 12:56:23 by tokazaki          #+#    #+#             */
/*   Updated: 2023/09/25 17:51:56 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include "minishell.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>

int		pipex(int argc, char *argv[], char **env);
void	firstfork(char **argv, int *pipefd, char **env);
void	lastfork(char **argv, int *pipefd, char **env);
void	waitchild(int pid);

char	*check_path(char *command, char **result);
void	malloc_error(void);

void	split_free(char **result);
void	error_exit(char *msg);
int		open_ee(char *str, int oflag, int orflag);
void	dup2_ee(int fd, int std);
void	close_ee(int fd);
void	exit_ee(int nbr);

void	fork_error_exit(char *msg);
#endif
