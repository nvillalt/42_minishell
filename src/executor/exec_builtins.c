#include "../../minishell.h"

static int	restore_fds(t_utils *utils)
{
	if (dup2(utils->saved_stdin, STDIN_FILENO) == -1)
		return (FUNC_FAILURE);
	close_redir_fd(&utils->saved_stdin);
	if (dup2(utils->saved_stdout, STDOUT_FILENO) == -1)
		return (FUNC_FAILURE);
	close_redir_fd(&utils->saved_stdin);
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
	int				redir_out;

	if (process->next || process_index != 0)
	{
		utils->pid_array[process_index] = fork();
		if (utils->pid_array[process_index] == -1)
			return(FUNC_FAILURE);
		if (utils->pid_array[process_index] == 0)
		{
			set_child_signals();
			close_redir_fd(&utils->main_pipe[0]);
			redirec_infile(utils, process);
			redir_out = redirec_outfile(utils, process);
			if (redir_out == 0 && process->next)
			{
				if (dup2(utils->main_pipe[1], STDOUT_FILENO) == -1)
					exit_process(utils);
			}
			close_redir_fd(&utils->main_pipe[1]);
			status = handle_builtins(utils, process);
			exit_process_custom(utils, status);
		}
	}
	else
	{
		utils->parent_builtin = 1;
		utils->saved_stdin = dup(STDIN_FILENO);
		if (utils->saved_stdin == -1)
		{
			perror("minishell");
			utils->status = 1;
			return (FUNC_FAILURE);
		}
		utils->saved_stdout = dup(STDOUT_FILENO);
		if (utils->saved_stdout == -1)
		{
			perror("minishell");
			utils->status = 1;
			return (FUNC_FAILURE);
		}
		utils->builtin_counter = 1;
		if (redirec_infile(utils, process) == -2)
		{
			utils->status = 1;
			return (FUNC_FAILURE);
		}
		if (redirec_outfile(utils, process) == -2)
		{
			utils->status = 1;
			return (FUNC_FAILURE);
		}
		status = handle_builtins(utils, process);
		utils->status = status;
		if (!restore_fds(utils))
		{
			utils->status = 1;
			perror("minishell");
			return (FUNC_FAILURE);
		}
		utils->parent_builtin = 0;
	}
	return (FUNC_SUCCESS);
}
