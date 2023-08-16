#include "microshell.h"

void	check_line(char *line)
{
	if (*line == '\n' || *line == '\0')
		ft_putstr_fd("", 1);
	else if (ft_strncmp(line, "echo ", 5) == 0)
		ft_putstr_fd(line + 5, 1);
	else if (ft_memcmp(line, "echo\n", 5) == 0)
		ft_putendl_fd("", 1);
	else if (ft_memcmp(line, "exit", 4) == 0)//EOFのshignalを受けとたら終了するように
		ex_exit();
	else
		ft_putstr_fd(ft_strjoin("builtin not found: ", line), 1);
}

int	main(void)
{
	char	*line;
	int		i;

	i = 0;
	while (1)
	{
		line = get_next_line(0);
		ft_printf("my-shell[%d]:",i);
		check_line(line);
		free (line);
		i++;
	}
	return (0);
}
