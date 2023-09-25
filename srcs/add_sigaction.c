/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sigaction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 14:04:34 by tokazaki          #+#    #+#             */
/*   Updated: 2023/09/25 17:53:49 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandla(int sig)
{
	if (sig == SIGINT)
		ft_printf("\n[sicnal]>> ");
	if (rl_on_new_line() == -1)
		exit(1);
	//	rl_replace_line("", 1);
	//	rl_on_new_line();
	//	rl_redisplay();
}

void	add_sigaction(void)
{
	//	struct sigaction sa_int;
	signal(SIGINT, sighandla);
	signal(SIGQUIT, SIG_IGN); // CTRL + /
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
