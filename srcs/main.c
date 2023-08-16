#include "microshell.h"

void	check_line(char *line)
{
	if (ft_strncmp(line, "exit", 4) == 0)
		ex_exit();
	else
		ft_putendl_fd(ft_strjoin("builtin not found: ", line), 1);
}

int	main(void)
{
	char	*line;

	while (1)
	{
		line = get_next_line(0);
		free (line);
		check_line(line);
	}
	return (0);
}
