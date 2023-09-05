#include "lexar_panda.h"

void	make_list(char *line, int len, t_list **list)
{
	ft_printf("[make list:");
	char	*result;

	result = ft_substr(line, 0, len);
	if (!result)
	{
//		status->error == 1;
		return ;
	}
	ft_printf(" %s]",result);
	ft_printf("[[%p]]",result);
	push_back(list, result);
}
