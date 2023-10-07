/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_error_mssage.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 19:47:59 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/07 19:49:43 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

void	erro_msg_no_such_file(t_info *status, char *content)
{
	error_printf("minishell: %s: No such file or directory\n", content);
	exit (127);
	(void)status;
}

void	erro_msg_is_a_directory(t_info *status, char *content)
{
	error_printf("%s: is a directory\n", content);
	exit (126);
	(void)status;
}

void	erro_msg_permission_denied(t_info *status, char *content)
{
	error_printf("%s: Permission denied\n", content);
	exit (126);
	(void)status;
}

void	erro_msg_not_command_found(t_info *status, char *content)
{
	error_printf("%s: command not found\n", content);
	exit (127);
	(void)status;
}
