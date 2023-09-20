/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panda_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:54:02 by tokazaki          #+#    #+#             */
/*   Updated: 2023/09/20 10:55:12 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_panda.h"
#include "minishell.h"

void	plusle_quote(char s, int *flag)
{
	if (s == '\'')
		*flag += S_QUOTE;
	else if (s == '\"')
		*flag += D_QUOTE;
}

void	minun_quote(char s, int *flag)
{
	if (s == '\'')
		*flag -= S_QUOTE;
	else if (s == '\"')
		*flag -= D_QUOTE;
}
