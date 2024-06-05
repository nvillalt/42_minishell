/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_first_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:22:00 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/05 15:58:21 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	execute_first_process(t_utils *utils, t_parse *process)
{
	int	last_infile;
	int	last_outfile;

	last_infile = -1;
	last_outfile = -1;
	set_child_signals();
	close_redir_fd(&utils->main_pipe[0]);
	open_files(utils, process, &last_infile, &last_outfile);
	redirec_infile(last_infile, utils);
	if (last_outfile == -1 && process->next)
	{
		if (dup2(utils->main_pipe[1], STDOUT_FILENO) == -1)
			exit_process(utils);
	}
	else
		redirec_outfile(last_outfile, utils);
	close_redir_fd(&utils->main_pipe[1]);
	close_fds(utils->process, utils);
	if (process->cmd && process->cmd[0])
		exec_cmd(utils, process);
	else
		exit_process_noerror(utils);
}

int	create_first_child(t_utils *utils, t_parse *process, int process_index)
{
	if (process->next)
	{
		if (pipe(utils->main_pipe) == -1)
			return (free_puterror_int(NULL, NULL, utils, 1));
	}
	if (process->built_in)
	{
		if (!exec_builtins(utils, process, process_index))
			return (FUNC_FAILURE);
	}
	else
	{
		utils->pid_array[process_index] = fork();
		if (utils->pid_array[process_index] == -1)
			return (free_puterror_int(NULL, NULL, utils, 1));
		if (utils->pid_array[process_index] == 0)
			execute_first_process(utils, process);
	}
	close_redir_fd(&utils->main_pipe[1]);
	return (FUNC_SUCCESS);
}
