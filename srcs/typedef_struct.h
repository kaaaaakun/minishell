/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef_struct.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tokazaki <tokazaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:40:57 by tokazaki          #+#    #+#             */
/*   Updated: 2023/09/28 13:53:07 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_STRUCT_H
# define TYPEDEF_STRUCT_H

# define BOTH_FREE 0
# define FIRST_FREE 1
# define SECOND_FREE 2
# define NEITHER_FREE 3

typedef struct s_list
{
	char			*content;
	int				flag;
	struct s_list	*next;
}	t_list;

typedef struct s_stack
{
	struct s_list		*outputlist;	//>
	struct s_list		*appendlist;	//>>
	struct s_list		*inputlist;		//<
	struct s_list		*heredoclist;	//<<
	struct s_list		*cmdlist;
	int					fork;
	struct s_stack		*next;
}	t_stack;

typedef struct s_info
{
	int				pid;
	int				pipe;
	int				error;
	int				exit_status;
	t_list			*env;
	char			*line;
	struct s_stack	*stack;
	int				cpy_stdin;
}	t_info;

#endif
