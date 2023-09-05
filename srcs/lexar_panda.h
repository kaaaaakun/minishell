#ifndef LEXER_MANDA_H
# define LEXER_MANDA_H

# include "minishell.h"

char	*make_list(int *flag, char *line, int len, t_list **list);
char	*serch_env(t_info *status, char *str);
void	lexar_panda_error_check(int *flag, t_info *status);
t_stack	*make_stack(t_info *status, t_stack *pre_data);
void	check_flag(t_info *status, char *result, int *flag);

#endif
