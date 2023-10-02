/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sigaction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 14:04:34 by tokazaki          #+#    #+#             */
/*   Updated: 2023/09/28 20:23:45 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

void	sighandler(int sig)
{
	if (sig == SIGINT)
		ft_printf("\n[sicnal]>> ");
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	sig_exit(int i)
{
	(void)i;
	ex_exit(NULL, NULL);
}

void	add_sigaction(int i)
{
	//	struct sigaction sa_int;
	// signal(SIGINT, sighandler);
	// signal(SIGQUIT, SIG_IGN); /*CTRL + \*/
	if (i == 0) /*コマンドの途中などではないとき*/
	{
		signal(SIGINT, sighandler);
		signal(SIGQUIT, SIG_IGN); /*CTRL + \*/
	}
	if (i == 1) /*parent process*/
	{
		signal(SIGCHLD, NULL);
		signal(SIGINT, sighandler);
		signal(SIGQUIT, SIG_IGN);
	}
	// if (i == 2) /*child process*/
	// if (i == 3) /*heredoc*/
	//	sigemptyset(&sa_int.sa_mask);
	//	sigaddset(&sa_int.sa_mask, SIGINT);
	//	sa_int.sa_handler = sa_sigint;
	//	sa_int.sa_flags = 0;
	//	if (sigaction(SIGINT, &sa_int, NULL) == -1)
	//	{
	//		perror("sigaction");
	//		ex_exit(NULL);
	//	}
}

// ctrl-C displays a new prompt on a new line.
// ctrl-D exits the shell. readlineにNULLが送られex_exitに入る
// ctrl-\ does nothing.

// signal, sigaction, sigemptyset, sigaddset

// parent, heredoc, child, main
// 子プロセスがいたら子プロセスをkill
// heredocがいたらheredocを終わらせる
// global 変数でのみ情報が引き渡される
