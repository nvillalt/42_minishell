/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_mid_process.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:22:45 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/06 17:22:00 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	infile_redirec_switch(t_utils *utils, int last_infile)
{
	if (last_infile == -1)
	{
		if (dup2(utils->main_pipe[0], STDIN_FILENO) == -1)
			exit_process(utils);
	}
	else
		redirec_infile(last_infile, utils);
}

static void	outfile_redirec_switch(t_utils *utils, int last_outfile)
{
	if (last_outfile == -1)
	{
		if (dup2(utils->aux_pipe[1], STDOUT_FILENO) == -1)
			exit_process(utils);
	}
	else
		redirec_outfile(last_outfile, utils);
}

static void	execute_mid_process(t_utils *utils, t_parse *process)
{
	unsigned char	status;
	int				last_infile;
	int				last_outfile;

	last_infile = -1;
	last_outfile = -1;
	set_child_signals();
	close_redir_fd(&utils->aux_pipe[0]);
	open_files(utils, process, &last_infile, &last_outfile);
	infile_redirec_switch(utils, last_infile);
	close_redir_fd(&utils->main_pipe[0]);
	outfile_redirec_switch(utils, last_outfile);
	close_redir_fd(&utils->aux_pipe[1]);
	close_fds(utils->process);
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

int	create_mid_child(t_utils *utils, t_parse *process, int process_index)
{
	if (pipe(utils->aux_pipe) == -1)
		return (free_puterror_int(NULL, NULL, utils, 1));
	close_redir_fd(&utils->main_pipe[1]);
	utils->pid_array[process_index] = fork();
	if (utils->pid_array[process_index] == -1)
		return (free_puterror_int(NULL, NULL, utils, 1));
	if (utils->pid_array[process_index] == 0)
		execute_mid_process(utils, process);
	close_redir_fd(&utils->main_pipe[0]);
	utils->main_pipe[0] = utils->aux_pipe[0];
	utils->main_pipe[1] = utils->aux_pipe[1];
	return (FUNC_SUCCESS);
}
