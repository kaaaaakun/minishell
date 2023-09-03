/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhino <hhino@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:14:07 by hhino             #+#    #+#             */
/*   Updated: 2023/09/03 21:21:56 by tokazaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ex_export(t_info *status, t_stack *data)
{
	return ;
	(void)status;
	(void)data;
}

//exportの後何もついていない場合は、declare -xを先頭につけ、=以下の文字列を""で囲む処理をする
//=の後に',"がついていない場合、spで区切られる前の文字列までのみ認識される
// bash-3.2$ export aaa=bbb
// bash-3.2$ export ccc="echo $aaa"
// bash-3.2$ $ccc
// bbb
// bash-3.2$ export aaa=bbb ccc
// bash-3.2$ export ccc="echo $aaa"
// bash-3.2$ $ccc
// bbb
