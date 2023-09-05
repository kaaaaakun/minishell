#include "lexar_panda.h"

t_stack	*make_stack(t_info *status, t_stack *pre_data)
{
	t_stack	*data;

	data = (t_stack *)malloc(sizeof(t_stack) * 1);
	if (!data)
		return (NULL);
	data->outputlist = NULL;
	data->appendlist = NULL;
	data->inputlist = NULL;
	data->heredoclist = NULL;
	data->cmdlist = NULL;
	data->next = NULL;
	if (status->stack == NULL)
		status->stack = data;
	else
		pre_data->next = data;
	return (data);
}
