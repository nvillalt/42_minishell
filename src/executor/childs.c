#include "../../minishell.h"

static void	init_pipe(int *pipe)
{
	pipe[0] = -1;
	pipe[1] = -1;
}

static int	wait_all_process(t_utils *utils)
{
	pid_t	pid;
	int		status;
	int		i;

	i = 0;
	while(i < utils->process_list_len)
	{
		pid = wait(&status);
		if (pid == -1)
			return (FUNC_FAILURE);
		if (pid == utils->pid_array[utils->process_list_len - 1])
		{
			if (WIFEXITED(status))
				utils->status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				utils->status = 128 + WTERMSIG(status);
			else if (WIFSTOPPED(status))
				utils->status = 128 + WSTOPSIG(status);
			else
				utils->status = status;
		}
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
	if (!create_first_child(utils, process, process_index))
		return (FUNC_FAILURE);
	process_index++;
	process = process->next;
	while(process && process->next != NULL)
	{
		if (create_mid_child(utils, process, process_index) == -1)
			return (FUNC_FAILURE);
		process = process->next;
		process_index++;
	}
	close_pipe_fd(&utils->main_pipe[1]);
	if (process)
	{
		if (!create_last_child(utils, process, process_index) == -1)
			return (FUNC_FAILURE);
	}
	close_pipe_fd(&utils->main_pipe[0]);
	if (!wait_all_process(utils))
		return (FUNC_FAILURE);
	return (FUNC_SUCCESS);
}
