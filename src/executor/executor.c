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

void	executor(t_utils *utils)
{
	int	process_list_len;
	int	process_count;

	process_list_len = process_counter(utils->process);
	open_multiple_heredocs(utils, utils->process);
	utils->pid_array = ft_calloc(process_list_len, sizeof(pid_t));
	if(!utils->pid_array)
	{
		perror(NULL);
		close_fds(utils->process, utils);
		free_utils(utils);
		exit(1);
	}
	process_count = 1;
	if (process_count == 1)
	{
		utils->pid_array[process_count - 1] = fork();
		if (utils->pid_array[process_count - 1] == -1)
		{
			perror(NULL);
			close_fds(utils->process, utils);
			free_lists(utils);
		}
		if (utils->pid_array[process_count - 1] == 0)
			execute_first_process(utils, utils->process); 
		wait(&utils->status);
		process_count++;
	}
/*
	else if (process_count < process_list_len)
		execute_mid_process(utils, main_pipe, aux_pipe);
	else if (process_count == process_list_len)
		execute_last_process(utils, main_pipe);
*/	
}
