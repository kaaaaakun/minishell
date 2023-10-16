/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:54:55 by hhino             #+#    #+#             */
/*   Updated: 2023/10/16 15:20:33 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_panda.h"

t_stack	*make_stack(t_info *status, t_stack *pre_data)
{
	t_stack	*data;

	data = (t_stack *)ft_calloc(sizeof(t_stack), 1);
	if (!data)
		return (NULL);
	data->outputlist = NULL;
	data->appendlist = NULL;
	data->inputlist = NULL;
	data->heredoclist = NULL;
	data->cmdlist = NULL;
	data->fork = 0;
	data->next = NULL;
	if (status->stack == NULL)
		status->stack = data;
	else
		pre_data->next = data;
	return (data);
}
