/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sigaction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 14:04:34 by tokazaki          #+#    #+#             */
/*   Updated: 2023/09/28 19:33:32 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

void	sighandl(int sig)
{
	if (sig == SIGINT)
		ft_printf("\n[sicnal]>> ");
	if (rl_on_new_line() == -1)
		exit(1);
	//	rl_replace_line("", 1);
	//	rl_on_new_line();
	//	rl_redisplay();
}

void	sig_exit(int i)
{
	(void)i;
	ex_exit(NULL, NULL);
}

void	add_sigaction(void)
{
	//	struct sigaction sa_int;
	// signal(SIGINT, sighandl);
	signal(SIGQUIT, sig_exit);
	signal(SIGQUIT, SIG_IGN); /*CTRL + \*/
	// if (g_sig_num == 0)
	// if (g_sig_num == 1)
	// if (g_sig_num == 2)
	// if (g_sig_num == 3)
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
// ctrl-D exits the shell.
// ctrl-\ does nothing.

// signal, sigaction, sigemptyset, sigaddset

// parent, heredoc, child, main
// 子プロセスがいたら子プロセスをkill
// heredocがいたらheredocを終わらせる
// global 変数でのみ情報が引き渡される
