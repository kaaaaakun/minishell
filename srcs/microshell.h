
#ifndef MICROSHELL_H
# define MICROSHELL_H

# include "libft.h"

void	check_command(char *line, char **env);
void	ex_env(char **split, char **env);
void	ex_unset(char **split, char **env);
void	ex_export(char **split, char **env);
void	ex_exit(char **split);
void	ex_echo(char **split);
void	ex_cd(char **split);
void	ex_pwd(char **split);
void	ex_execve(char **split);
int		main(int argc, char *argv[], char **env);

#endif
