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
   // シグナルセットを初期化し、SIGINT シグナルをセットに追加
    
	sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);

	sa_int.sa_handler = sa_sigint;
	sa_int.sa_flags = 0;
	// 2. シグナルハンドラを設定します。
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
	{
		perror("sigaction");
		ex_exit(NULL);
	}
	ft_putendl_fd("set signal int", 1);
}

void	sa_sigint(int signum)
{
	(void)signum;
	ft_putendl_fd("signal int", 1);
	check_command("");
//	rl_on_new_line();
//	main();
	line_read();
}
