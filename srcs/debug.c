/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:46:29 by tokazaki          #+#    #+#             */
/*   Updated: 2023/09/05 20:35:18 by hhino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_data(void *data)
{
    ft_printf("%s\n", (char *)data);
}

void	lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f (lst->content);
		lst = lst->next;
	}
}
void	debug(t_info *status,char *str)
{
	ft_printf("---------[%s]---------\n",str);
	t_stack *data;
	data = status->stack;
	while (data != NULL)
	{
//		ft_printf("envの中身を全て表示\n");
//		lstiter(status->env, print_data);//listの中身を表示
		ft_printf("\n[outputlist]\n");
		lstiter(data->outputlist, print_data);//
		ft_printf("\n[appendlist]\n");
		lstiter(data->appendlist, print_data);//
		ft_printf("\n[inputlist]\n");
		lstiter(data->inputlist, print_data);//
		ft_printf("\n[heredoclist]\n");
		lstiter(data->heredoclist, print_data);//
		ft_printf("\n[cmdlist]\n");
		lstiter(data->cmdlist, print_data);//
		data = data->next;
		if (data != NULL)
			ft_printf("\n---------pipe----------\n");
	}
	ft_printf("-----------------------\n");
}
