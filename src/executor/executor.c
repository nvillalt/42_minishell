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

static int	create_pid_array(t_utils *utils)
{
	utils->process_list_len = process_counter(utils->process);
	utils->pid_array = ft_calloc(utils->process_list_len, sizeof(pid_t));
	if (!utils->pid_array)
		return(FUNC_FAILURE);
	return(FUNC_SUCCESS);
}

int	executor(t_utils *utils, t_parse *process)
{
	utils->builtin_counter = 0;
	if (!create_multiple_heredocs(utils, utils->process))
		return (FUNC_FAILURE);
	if (!create_pid_array(utils))
		return (FUNC_FAILURE);
	if (!execute_childs(utils, process))
		return (FUNC_FAILURE);
	set_signals();
	return (FUNC_SUCCESS);
}
