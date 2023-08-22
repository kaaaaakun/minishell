/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sigaction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 14:04:34 by tokazaki          #+#    #+#             */
/*   Updated: 2023/08/22 12:54:08 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sa_sigint(int signum);

void	add_sigaction(void)
{
	struct sigaction sa_int;

	sigemptyset(&sa_int.sa_mask);
	sigaddset(&sa_int.sa_mask, SIGINT);
	sa_int.sa_handler = sa_sigint;
	sa_int.sa_flags = 0;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
	{
		perror("sigaction");
		ex_exit(NULL);
	}
}

void	sa_sigint(int signum)
{
	(void)signum;
	ft_putstr_fd("[signint]", 1);
	ft_putendl_fd("", 1);
	rl_on_new_line();
	line_read();
}
