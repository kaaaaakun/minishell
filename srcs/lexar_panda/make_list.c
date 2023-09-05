#include "lexar_panda.h"

void	make_list(int *flag, char *line, int len, t_list **list)
{
	char	*result;

	result = ft_substr(line, 0, len);
	if (!result)
	{
//		status->error == 1;
		return ;
	}
	push_back(list, result);
	(void)flag;
}
