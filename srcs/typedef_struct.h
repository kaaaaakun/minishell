/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef_struct.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:40:57 by tokazaki          #+#    #+#             */
/*   Updated: 2023/09/24 17:13:34 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_STRUCT_H
# define TYPEDEF_STRUCT_H

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
	int				pre_pipe1;
	int				pre_pipe0;
	int				error;
	int				exit_status;
	int				exec_count;
	t_list			*env; //exportの中身をpush_backする, unsetで消す
	char			*line;
	struct s_stack	*stack;
	struct s_flist	*flist;
	int				cpy_stdin;
}	t_info;

#endif
