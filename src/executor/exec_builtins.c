#include "../../minishell.h"

static int	restore_fds(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	return (FUNC_SUCCESS);
}

unsigned char	handle_builtins(t_utils *utils, t_parse *process)
{
	unsigned char	status;

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
	unsigned char	status;
	int				saved_stdin;
	int				saved_stdout;

	if (process->next || process_index != 0)
	{
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
		printf("entra\n");
		saved_stdin = dup(STDIN_FILENO);
		saved_stdout = dup(STDOUT_FILENO);
		utils->builtin_counter = 1;
		redirec_infile(utils, process);
		if (!redirec_outfile(utils, process) && process->next)
		{
			if (dup2(utils->main_pipe[1], STDOUT_FILENO) == -1)
				exit_process(utils);
		}
		close_pipe_fd(&utils->main_pipe[1]);
		status = handle_builtins(utils, process);
		utils->status = status;
		restore_fds(saved_stdin, saved_stdout);
	}
	return (FUNC_SUCCESS);
}
