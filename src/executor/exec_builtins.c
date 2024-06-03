/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:18:48 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/03 16:19:37 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		status = ft_pwd(utils->env);
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

static void	set_child_builtin(t_utils *utils, t_parse *process, int redir_out)
{
	unsigned char	status;

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

static int	set_parent_builtin(t_utils *utils, t_parse *process, int redir_out)
{
	unsigned char	status;

	utils->parent_builtin = 1;
	utils->saved_stdin = dup(STDIN_FILENO);
	if (utils->saved_stdin == -1)
		return (free_puterror_int(NULL, NULL, utils, 1));
	utils->saved_stdout = dup(STDOUT_FILENO);
	if (utils->saved_stdout == -1)
		return (free_puterror_int(NULL, NULL, utils, 1));
	utils->builtin_counter = 1;
	if (redirec_infile(utils, process) == -2)
		return (change_status(utils, 1));
	if (redirec_outfile(utils, process) == -2)
		return (change_status(utils, 1));
	status = handle_builtins(utils, process);
	utils->status = status;
	if (!restore_fds(utils))
		return (free_puterror_int(NULL, NULL, utils, 1));
	utils->parent_builtin = 0;
	return (FUNC_SUCCESS);
}

int	exec_builtins(t_utils *utils, t_parse *process, int process_index)
{
	int				redir_out;

	if (process->next || process_index != 0)
	{
		utils->pid_array[process_index] = fork();
		if (utils->pid_array[process_index] == -1)
			return (FUNC_FAILURE);
		if (utils->pid_array[process_index] == 0)
			set_child_builtin(utils, process, redir_out);
	}
	else
	{
		if (!set_parent_builtin(utils, process, redir_out))
			return (FUNC_FAILURE);
	}
	return (FUNC_SUCCESS);
}
