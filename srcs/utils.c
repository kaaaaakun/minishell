/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:42:02 by hhino             #+#    #+#             */
/*   Updated: 2023/10/07 19:30:34 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_panda.h"

pid_t	fork_ee(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		error_exit("fork");
	return (pid);
}

t_stack	*search_last_stack(t_info *status)
{
	t_stack	*data;

	data = status->stack;
	while (data->next != NULL)
		data = data->next;
	return (data);
}

char	*mini_ft_strchr(const char *s, int c)
{
	char	*str;
	char	chr;
	int		flag;

	if (!s)
		return (NULL);
	str = (char *)s;
	chr = (char)c;
	flag = INITIAL;
	while (*str || chr == '\0')
	{
		if ((*str == '\'' || *str == '\"') && !(flag & IN_QUOTE))
			plusle_quote(*str, &flag);
		else if ((*str == '\'' && flag & S_QUOTE) || \
			(*str == '\"' && flag & D_QUOTE))
			minun_quote(*str, &flag);
		else if (*str == chr && !(flag & IN_QUOTE))
			return (str);
		str++;
	}
	return (NULL);
}
