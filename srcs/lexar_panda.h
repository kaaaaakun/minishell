#ifndef LEXER_MANDA_H
# define LEXER_MANDA_H

# include "minishell.h"

void	make_list(char *line, int len, t_list **list);
char	*serch_env(t_info *status, char *str);
void	lexar_panda_error_check(int *flag, t_info *status);

#endif
