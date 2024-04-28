#include "../../minishell.h"

static void	init_pipe(int *pipe)
{
	pipe[0] = -1;
	pipe[1] = -1;
}

static int	wait_all_process(t_utils *utils)
{
	int	i;

	i = 0;
	while(i < utils->process_list_len)
	{
		if (waitpid(utils->pid_array[i], &utils->status, 0) == -1)
			return (FUNC_FAILURE);
		i++;
	}
	return (FUNC_SUCCESS);
}

int	execute_childs(t_utils *utils, t_parse *process)
{
	int	process_index;

	process_index = 0;
	init_pipe(utils->main_pipe); //ESTO PODEMOS HACERLO EN EL INIT DE UTILS
	init_pipe(utils->aux_pipe);
	if (!create_first_child(utils, process_index))
		return (FUNC_FAILURE);
	process_index++;
	process = process->next;
	/*
	while(process && process->next != NULL)
	{
		if (create_mid_process(utils, process) == -1)
			return (FUNC_FAILURE);
		process = process->next;
		process_index++;
	}
	*/
	close_pipe_fd(utils->main_pipe[1]);
	if (process)
	{
		if (!create_last_child(utils, process, process_index) == -1)
			return (FUNC_FAILURE);
	}
	if (!wait_all_process(utils))
		return (FUNC_FAILURE);
	return (FUNC_SUCCESS);
}
