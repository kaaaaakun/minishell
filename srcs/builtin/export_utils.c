/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 17:06:49 by hhino             #+#    #+#             */
/*   Updated: 2023/10/12 19:30:46 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_with_doublequotes(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '=')
			ft_putchar_fd(str[i], 1);
		else if (str[i] == '=')
		{
			ft_putchar_fd(str[i], 1);
			ft_putchar_fd('"', 1);
		}
		i++;
	}
	ft_putchar_fd('"', 1);
}

int	valid_left(char *str, int flag)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[i]) == 0 && str[i] != '_')
		return (0);
	if (flag == 0)
	{
		while (str[i] != '=' && str[i] != '\0')
		{
			if (ft_isalnum(str[i]) == 0 && str[i] != '_')
				return (0);
			i++;
		}
	}
	else if (flag == 1)
	{
		while (str[i] != '+')
		{
			if (ft_isalnum(str[i]) == 0 && str[i] != '_')
				return (0);
			i++;
		}
	}
	return (1);
}

int	plus_equal_or_not(char *str)
{
	int	i;

	i = 0;
	if (ft_strnstr(str, "+=", ft_strlen(str)) != NULL)
	{
		while (str[i] != '+')
		{
			if (str[i] == '=')
				return (0); //=
			i++;
		}
		return (1); //+=
	}
	else
		return (0); //= or '\0'
}

char	*no_left_but_plus(char *str)
{
	int		i;
	char	*s1;
	char	*s2;
	char	*ans;

	i = 0;
	while (str[i] != '+')
		i++;
	s1 = ft_substr(str, 0, i);
	s2 = ft_substr(str, i + 1, ft_strlen(str) - i - 1);
	ans = ft_strjoin_free(s1, s2, NEITHER_FREE);
	free(s1);
	free(s2);
	free(str);
	return (ans);
}

void	print_export_env(t_list *env)
{
	while (env != NULL)
	{
		ft_printf("declare -x ");
		if (ft_strchr(env->content, '='))
			print_with_doublequotes(env->content);
		else
			ft_printf("%s", env->content);
		ft_putchar_fd('\n', 1);
		env = env->next;
	}
}
