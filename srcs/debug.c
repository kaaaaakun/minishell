/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:46:29 by tokazaki          #+#    #+#             */
/*   Updated: 2023/09/10 10:49:01 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_data(void *data)
{
    d_printf("%s\n", (char *)data);
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
	d_printf("\n---------[%s]---------\n",str);
	t_stack *data;
	data = status->stack;
	while (data != NULL)
	{
		d_printf("\n[outputlist]\n");
		lstiter(data->outputlist, print_data);//
		d_printf("\n[appendlist]\n");
		lstiter(data->appendlist, print_data);//
		d_printf("\n[inputlist]\n");
		lstiter(data->inputlist, print_data);//
		d_printf("\n[heredoclist]\n");
		lstiter(data->heredoclist, print_data);//
		d_printf("\n[cmdlist]\n");
		lstiter(data->cmdlist, print_data);//
		data = data->next;
		if (data != NULL)
			d_printf("\n---------pipe----------\n");
	}
	d_printf("-----------------------\n\n");
}

void	debug_env(t_info *status,char *str)
{
	d_printf("\n---------[env]---------\n",str);
	t_stack *data;
	data = status->stack;
	while (data != NULL)
	{
		d_printf("envの中身を全て表示\n");
		lstiter(status->env, print_data);//listの中身を表示
	}
	d_printf("-----------------------\n\n");
}
