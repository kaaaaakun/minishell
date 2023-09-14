#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

//pino.c
void	init_stack(t_info *status);
void	put_to_list(char *line, t_stack *stack);
char	*put_space(char *line);
void	check_line(char *line, t_info *status);


#endif
