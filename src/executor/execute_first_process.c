#include "../../minishell.h"

static void	execute_first_process(t_utils *utils, t_parse *process)
{
	redirec_infile(utils, process);
	close_pipe_fd(&utils->main_pipe[0]);
	if (!redirec_outfile(utils, process))
	{
		if (process->next)
		{
			if (dup2(utils->main_pipe[1], STDOUT_FILENO) == -1)
				exit_process(utils);
		}
	}
	close_pipe_fd(&utils->main_pipe[1]);
	if (process->cmd && process->cmd[0]) //Cuando llegue el parseo bueno es posible que toque cambiarlo
		exec_cmd(utils, process);
	else
		exit_process_noerror(utils);
}

int	create_first_child(t_utils *utils, int process_index)
{
	if (utils->process->next)
	{
		if (pipe(utils->main_pipe) == -1)
			return(FUNC_FAILURE);
	}
	utils->pid_array[process_index] = fork();
	if (utils->pid_array[process_index] == -1)
		return(FUNC_FAILURE);
	if (utils->pid_array[process_index] == 0)
		execute_first_process(utils, utils->process);
	return (FUNC_SUCCESS);
}
