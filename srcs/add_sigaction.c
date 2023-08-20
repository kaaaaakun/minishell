/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sigaction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 14:04:34 by tokazaki          #+#    #+#             */
/*   Updated: 2023/08/20 20:42:54 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sa_sigint(int signum);

void	add_sigaction(void)
{
	struct sigaction sa_int;

	sa_int.sa_handler = sa_sigint;
	sa_int.sa_flags = 0;
	// 2. シグナルハンドラを設定します。
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
	{
		perror("sigaction");
		ex_exit(NULL);
	}
}

void	sa_sigint(int signum)
{
	(void)signum;
	check_command("");
}
