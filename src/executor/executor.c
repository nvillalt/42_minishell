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
	int	process_index;
	int	status;
	pid_t pid;

	process_list_len = process_counter(utils->process);
	open_multiple_heredocs(utils, utils->process);
	close_fds(utils->process, utils);
	free_lists(utils);
	/*
	process_index = 1;
	if (process_index == 1)
	{
		pid = fork();
		if (pid == 0)
			execute_first_process(utils, main_pipe);
		wait(&status);
	}
	else if (process_index < process_list_len)
		execute_mid_process(utils, main_pipe, aux_pipe);
	else if (process_index == process_list_len)
		execute_last_process(utils, main_pipe);
*/	
	return (0);
}
