#include "microshell.h"

void	check_line(char *line, char **env)
{
	int i;

	i = 0;
	if (*line == '\n' || *line == '\0')
		ft_putstr_fd("", 1);
	else if (ft_strncmp(line, "echo ", 5) == 0)
		ft_putstr_fd(line + 5, 1);
	else if (ft_memcmp(line, "echo\n", 5) == 0)
		ft_putendl_fd("", 1);
	else if (ft_strncmp(line, "env", 3) == 0)
		while(env[i] != NULL)
		{
			ft_putendl_fd(env[i], 1);
			i++;
		}
	else if (ft_memcmp(line, "exit", 4) == 0)//EOFのshignalを受けとたら終了するように
		ex_exit();
	else
		ft_putstr_fd(ft_strjoin("builtin not found: ", line), 1);
}

int	main(int argc, char *argv[], char **env)
{
	char	*line;
	int		i;

	i = 0;
	(void)argc;
	(void)argv;
	while (1)
	{
		ft_printf("my-shell[%d]:",i);
		line = get_next_line(0);
		check_line(line, env);
		free (line);
		i++;
	}
	return (0);
}
