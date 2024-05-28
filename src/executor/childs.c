#include "../../minishell.h"
/*
static char	**create_cmd_no_builtin(char **cmd) 
{
	char	**new_cmd;

	new_cmd = env_dup(cmd + 1);
	if (!new_cmd)
		return (NULL);
	free_matrix(cmd);
	return (new_cmd);
}

static int	clean_env_builtin(t_parse *process)
{
	while (process)
	{
		if (process->built_in == ENV && count_matrix(process->cmd) > 1)
		{
			process->cmd = create_cmd_no_builtin(process->cmd);
			if (!process->cmd)
				return (FUNC_FAILURE);
			process->built_in = 0;
		}
		process = process->next;
	}
	return (FUNC_SUCCESS);
}
*/
static int	get_cmd_num(t_parse *process)
{
	int	cmd_num;

	cmd_num = 0;
	while(process)
	{
		cmd_num++;
		process = process->next;
	}
	return(cmd_num);
}

static int	wait_all_process(t_utils *utils)
{
	int	i;
	int	pid;
	int	status;
	int	cmd_num;

	i = 0;
	cmd_num = get_cmd_num(utils->process);
	while(i < (cmd_num - utils->builtin_counter))
	{
		pid = wait(&status);
		if (pid == -1)
		{
			perror("minishell");
			utils->status = 1; //AL LORO CON ESTO
			return (FUNC_FAILURE);
		}
		if (pid == utils->pid_array[cmd_num - 1])
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
	if (!create_first_child(utils, process, process_index))
		return (FUNC_FAILURE);
	process_index++;
	process = process->next;
	while(process && process->next != NULL)
	{
		if (!create_mid_child(utils, process, process_index))
			return (FUNC_FAILURE);
		process = process->next;
		process_index++;
	}
	close_redir_fd(&utils->main_pipe[1]);
	if (process)
	{
		if (!create_last_child(utils, process, process_index))
			return (FUNC_FAILURE);
	}
	close_redir_fd(&utils->main_pipe[0]);
	if (!wait_all_process(utils))
		return (FUNC_FAILURE);
	return (FUNC_SUCCESS);
}
