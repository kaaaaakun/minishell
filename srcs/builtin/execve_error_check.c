/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_error_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 19:50:35 by tokazaki          #+#    #+#             */
/*   Updated: 2023/10/07 21:11:12 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

void	erro_msg_no_such_file(t_info *status, char *content);
void	erro_msg_is_a_directory(t_info *status, char *content);
void	erro_msg_permission_denied(t_info *status, char *content);
void	erro_msg_not_command_found(t_info *status, char *content);

void	is_no_file_error(t_info *status)
{
	char	*content;

	content = status->stack->cmdlist->content;
	if (content[0] == '.' || content[0] == '/')
		erro_msg_no_such_file(status, content);
	else
		erro_msg_not_command_found(status, content);
}

void	is_directory_error(t_info *status, char *path)
{
	char	*content;

	content = status->stack->cmdlist->content;
	if (content[0] == '.' || path[0] == '/')
		erro_msg_is_a_directory(status, content);
	if (content[0] == '/')
		erro_msg_no_such_file(status, content);
	else
		erro_msg_not_command_found(status, content);
}

void	is_non_xok(t_info *status)
{
	char	*content;

	content = status->stack->cmdlist->content;
	if (content[0] == '.' && content[1] == '/')
		erro_msg_permission_denied(status, content);
	if (content[0] == '/')
		erro_msg_no_such_file(status, content);
	else
		erro_msg_not_command_found(status, content);
}
