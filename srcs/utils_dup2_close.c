/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dup2_close.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 15:57:38 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/07 19:28:23 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_panda.h"

void	close_pipe(t_info *status, int *pipefd)
{
	close_ee(status, pipefd[0]);
	close_ee(status, pipefd[1]);
}

void	skip_space(char *post_word, int *i)
{
	while (post_word[*i] == ' ' || post_word[*i] == '	')
		*i += 1;
}

void	dup2_close_pipe(t_info *status, int *pipefd, int flag)
{
	if (flag == PIPE_IN)
		dup2_ee(status, pipefd[0], flag);
	else if (flag == PIPE_OUT)
		dup2_ee(status, pipefd[1], flag);
	close_pipe(status, pipefd);
}
