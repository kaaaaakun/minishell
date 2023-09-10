#include "minishell.h"

char	*replace_env(char *line, t_info *status)
{
	char *line_start;
	char *s1;
	char *s2;
	char *tmp;

	s1 = ft_strdup("");
	while (*line != '\0')
	{
		line_start = line;
		line = ft_strchr(line, '$');
		if (line == NULL)
			break ;
		s2 = NULL;
		tmp = s1;
		s1 = ft_strjoin(s1, s2);
		free(tmp);
	}
	free(s2);
	return (s1);
	(void)line;
	(void)status;
	(void)line_start;
}
