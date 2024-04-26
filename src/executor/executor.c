#include "../../minishell.h"

static int	process_counter(t_parse *process)
{
	int	i;

	i = 0;
	while(process)
	{
		process = process->next;
		i++;
	}
	return (i);
}

int	executor(t_utils *utils)
{
	int	process_list_len;

	process_list_len = process_counter(utils->process);
	if (!create_multiple_heredocs(utils, utils->process))
		return (FUNC_FAILURE);
	utils->pid_array = ft_calloc(process_list_len, sizeof(pid_t));
	if(!utils->pid_array)
		return (FUNC_FAILURE);
	if (!execute_childs(utils, process_list_len))
		return (FUNC_FAILURE);
	return (FUNC_SUCCESS);
}
