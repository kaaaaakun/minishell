
#ifndef MICROSHELL_H
# define MICROSHELL_H

# include "libft.h"

void	check_line(char *line, char **env);
void	ex_exit();
int		main(int argc, char *argv[], char **env);

#endif
