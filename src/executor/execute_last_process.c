#include "../../minishell.h"

static void	execute_last_process(t_utils *utils, t_parse *process)
{
	unsigned char	status;

	if (!redirec_infile(utils, process))
	{
		if (dup2(utils->main_pipe[0], STDIN_FILENO) == -1)
			exit_process(utils);
	}
	close_pipe_fd(&utils->main_pipe[0]);
	redirec_outfile(utils, process);
	if (process->built_in)
	{
		status = handle_builtins(utils, process);
		exit_process_custom(utils, status);
	}
	else
		exec_cmd(utils, process);
}

int	create_last_child(t_utils *utils, t_parse *process, int process_index)
{
	utils->pid_array[process_index] = fork();
	if (utils->pid_array[process_index] == -1)
		return (FUNC_FAILURE);
	if (utils->pid_array[process_index] == 0)
		execute_last_process(utils, process);
	return (FUNC_SUCCESS);
}
