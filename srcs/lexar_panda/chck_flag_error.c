#include "minishell.h"

void	lexar_panda_error_check(int *flag, t_info *status)
{
	if (*flag & D_QUOTE)
				ft_putendl_fd(" \"syntax error `\"'", 1);
	if (*flag & S_QUOTE)
				ft_putendl_fd(" \"syntax error `\''", 1);
	if (*flag & NEED_FILE)
				ft_putendl_fd(" \"syntax error `< << > >>'", 1);
	if (!(*flag = COMMAND))
				ft_putendl_fd(" \"syntax error `|'", 1);
	(void)status;
}
