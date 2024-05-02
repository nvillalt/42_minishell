#include "../../minishell.h"

static int	handle_builtins(t_utils *utils, t_parse *process)
{
	int	status;

	if (process->built_in == ECHO)
		status = ft_echo(process->cmd);
	if (process->built_in == PWD)
		status = ft_pwd();
	if (process->built_in == ENV)
		status = ft_env(utils->env, process->cmd);
	if (process->built_in == UNSET)
		status = ft_unset(utils, process->cmd);
	if (process->built_in == CD)
		status = ft_cd(utils, process->cmd);
	if (process->built_in == EXIT)
		ft_exit(process->cmd, utils);
	if (process->built_in == EXPORT)
		status = ft_export(utils, process->cmd);
	return (status);
}

int	exec_builtins(t_utils *utils, t_parse *process, int process_index)
{
	int	status;

	if (process->next || process_index != 0)
	{
		utils->builtin_counter = 0;
		utils->pid_array[process_index] = fork();
		if (utils->pid_array[process_index] == -1)
			return(FUNC_FAILURE);
		if (utils->pid_array[process_index] == 0)
		{
			status = handle_builtins(utils, process);
			exit_process_custom(utils, status);
		}
	}
	else
	{
		utils->builtin_counter = 1;
		status = handle_builtins(utils, process);
		utils->status = status;
	}
	return (FUNC_SUCCESS);
}
