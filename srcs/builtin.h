#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

//pino.c
void	init_stack(t_info *status);
void	put_to_list(char *line, t_stack *stack);
char	*put_space(char *line);
void	check_line(char *line, t_info *status);

void	ex_cd(t_info *status, t_stack *data);
void	ex_echo(t_info *status, t_stack *data);
void	ex_env(t_info *status, t_stack *data);
void	ex_exit(t_info *status, t_stack *data);
void	ex_export(t_info *status, t_stack *data);
void	ex_pwd(void);
void	ex_unset(t_info *status, t_stack *data);

//export_utils
void	insert_doublequotes(char *str);
int		valid_left(char *str, int flag);
int		plus_equal_or_not(char *str);
char	*no_left_but_plus(char *str);
void	print_export_env(t_list *env);

#endif
