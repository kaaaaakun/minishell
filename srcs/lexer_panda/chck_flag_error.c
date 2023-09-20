#include "minishell.h"
#include "lexer_panda.h"

void	lexer_panda_error_check(int *flag, t_info *status)
{
	if (*flag & D_QUOTE)
				ft_putendl_fd(" \"minishell: syntax error near unexpected token `\"'", 1);
	if (*flag & S_QUOTE)
				ft_putendl_fd(" \"minishell: syntax error near unexpected token `\''", 1);
	if (*flag & NEED_FILE)
				ft_putendl_fd(" \"minishell: syntax error near unexpected token `newline'", 1);
	if (!(*flag & COMMAND))
				ft_putendl_fd(" \"minishell: syntax error near unexpected token `|'", 1);
	ft_putendl_fd(" erro check ", 1);
	(void)status;
}
