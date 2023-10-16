/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sigaction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 14:04:34 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/15 19:39:00 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

void	sighandler_sigint(int sig)
{
	(void)sig;
	rl_on_new_line();
	ft_printf("\n");
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal = 2;
}

void	sighandler_heredoc(int sig)
{
	(void)sig;
	close(0);
	g_signal = SIGINT;
}

void	sighandler_child(int sig)
{
	if (sig == SIGINT)
	{
		write(STDIN_FILENO, "\n", 1);
		g_signal = 130;
	}
	if (sig == SIGQUIT)
	{
		write(STDIN_FILENO, "\n", 1);
		g_signal = 131;
	}
}

void	add_sigaction(t_info *status, int flag)
{
	struct sigaction	sa;

	if (g_signal == SIGINT)
		status->exit_status += 0;
	sigemptyset(&sa.sa_mask);
	if (flag == 0)
	{
		signal(SIGINT, sighandler_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (flag == 1)
	{
		signal(SIGINT, sighandler_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (flag == 2)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (flag == 4)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}

//// void	add_sigaction(int flag)
//// {
//// 	signal(SIGINT, sighandler_sigint); /*ctrl+C*/
//// 	signal(SIGQUIT, SIG_IGN); /*CTRL + \*/
//	//	sigemptyset(&sa_int.sa_mask);
//	//	sigaddset(&sa_int.sa_mask, SIGINT);
//	//	sa_int.sa_handler = sa_sigint;
//	//	sa_int.sa_flags = 0;
//	//	if (sigaction(SIGINT, &sa_int, NULL) == -1)
//	//	{
//	//		perror("sigaction");
//	//		ex_exit(NULL);
//	//	}
//// }
//
//// ctrl-C displays a new prompt on a new line.
//// ctrl-D exits the shell. readlineにNULLが送られex_exitに入る
//// ctrl-\ does nothing.
//
//// signal, sigaction, sigemptyset, sigaddset
//
//// parent, heredoc, child, main
//// 子プロセスがいたら子プロセスをkill
//// heredocがいたらeredocを終わらせる
//// global 変数でのみ情報が引き渡される
