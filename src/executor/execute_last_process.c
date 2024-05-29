#include "../../minishell.h"

static void	execute_last_process(t_utils *utils, t_parse *process)
{
	unsigned char	status;

	set_child_signals();
	close_redir_fd(&utils->main_pipe[1]);
	if (!redirec_infile(utils, process))
	{
		if (dup2(utils->main_pipe[0], STDIN_FILENO) == -1)
			exit_process(utils);
	}
	close_redir_fd(&utils->main_pipe[0]);
	redirec_outfile(utils, process);
	if (process->built_in)
	{
		status = handle_builtins(utils, process);
		exit_process_custom(utils, status);
	}
	else if (process->cmd && process->cmd[0])
		exec_cmd(utils, process);
	else
		exit_process_noerror(utils);
}

int	create_last_child(t_utils *utils, t_parse *process, int process_index)
{
	utils->pid_array[process_index] = fork();
	if (utils->pid_array[process_index] == -1)
		return (free_puterror_int(NULL, NULL, utils, 1));
	if (utils->pid_array[process_index] == 0)
		execute_last_process(utils, process);
	close_redir_fd(&utils->main_pipe[0]);
	return (FUNC_SUCCESS);
}
