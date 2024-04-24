#include "../../minishell.h"

int	create_first_child(t_utils *utils, int process_count)
{
	utils->pid_array[process_count - 1] = fork();
	if (utils->pid_array[process_count - 1] == -1)
		return(0);
	if (utils->pid_array[process_count - 1] == 0)
		execute_first_process(utils, utils->process); 
	wait(&utils->status);
	process_count++;
	return (FUNC_SUCCESS);
}

int	execute_childs(t_utils *utils, int process_list_len)
{
	int	process_count;

	process_count = 1;
	if (process_count == 1)
	{
		create_first_child(utils, process_count);
		if (!create_first_child)
			return (FUNC_FAILURE);
	}
	return (FUNC_SUCCESS);
}