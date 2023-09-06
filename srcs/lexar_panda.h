#ifndef LEXER_MANDA_H
# define LEXER_MANDA_H

# include "minishell.h"

//
# define INITIAL 0x000
# define AT_PIPE 0x001
# define COMMAND 0x002

# define D_QUOTE 0x004
# define S_QUOTE 0x008
# define IN_QUOTE S_QUOTE + D_QUOTE 

# define INPUT_REDIRECT 0x010
# define HEREDOC 0x020
# define OUTPUT_REDIRECT 0x040
# define APPENDDOC 0x080
# define NEED_FILE INPUT_REDIRECT + HEREDOC + OUTPUT_REDIRECT + APPENDDOC

# define ERROR 0x200
# define NOFLAG 0x400
//

char	*make_list(int *flag, char *line, int len, t_list **list);
char	*serch_env(t_info *status, char *str);
void	lexar_panda_error_check(int *flag, t_info *status);
t_stack	*make_stack(t_info *status, t_stack *pre_data);
void	check_flag(t_info *status, char *result, int *flag);

//utils
void	free_null(void *ptr);

#endif
