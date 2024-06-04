/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_first_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:22:00 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/04 23:00:51 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	open_minus(t_utils *utils, t_parse *process, int last_infile)
{
	process->redirec->fd = open(process->redirec->doc, O_RDONLY);
	if (process->redirec->fd == -1)
	{
		ft_puterror(process->redirec->doc);
		if (utils->parent_builtin == 1)
			return (-2);
		else
			exit_process(utils);
	}
	last_infile = process->redirec->fd;
	return (last_infile);
}
static int	open_heredoc(t_utils *utils, t_parse *process, int last_infile)
{
	process->redirec->fd = open(process->redirec->heredoc_file, O_RDONLY);
	if (process->redirec->fd == -1)
	{
		ft_puterror(process->redirec->doc);
		if (utils->parent_builtin == 1)
			return (-2);
		else
			exit_process(utils);
	}
	last_infile = process->redirec->fd;
	return (last_infile);
}

static int	open_great(t_utils *utils, t_parse *process, int last_outfile)
{
	process->redirec->fd = open(process->redirec->doc,
			O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (process->redirec->fd == -1)
	{
		ft_puterror(process->redirec->doc);
		if (utils->parent_builtin == 1)
			return (-2);
		else
			exit_process(utils);
	}
	last_outfile = process->redirec->fd;
	return (last_outfile);
}

static int	open_append(t_utils *utils, t_parse *process, int last_outfile)
{
	process->redirec->fd = open(process->redirec->doc,
			O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (process->redirec->fd == -1)
	{
		ft_puterror(process->redirec->doc);
		if (utils->parent_builtin == 1)
			return (-2);
		else
			exit_process(utils);
	}
	last_outfile = process->redirec->fd;
	return (last_outfile);
}

static void	open_files(t_utils *utils, t_parse *process, int *last_infile, int *last_outfile)
{
	while (process->redirec)
	{
		if (process->redirec->redir_type == MINUS)
		{
			*last_infile = open_minus(utils, process, *last_infile);
			if (*last_infile == -2)
				return ;
		}
		else if (process->redirec->redir_type == HEREDOC)
		{
			*last_infile = open_heredoc(utils, process, *last_infile);
			if (*last_infile == -2)
				return ;
		}
		else if (process->redirec->redir_type == GREAT)
		{
			*last_outfile = open_great(utils, process, *last_outfile);
			if (*last_outfile == -2)
				return ;
		}
		else if (process->redirec->redir_type == APPEND)
		{
			*last_outfile = open_append(utils, process, *last_outfile);
			if (*last_outfile == -2)
				return ;
		}
		process->redirec = process->redirec->next;
	}
}

static void	execute_first_process(t_utils *utils, t_parse *process)
{
	int	last_infile;
	int	last_outfile;

	last_infile = -1;
	last_outfile = -1;
	set_child_signals();
	close_redir_fd(&utils->main_pipe[0]);
	open_files(utils, process, &last_infile, &last_outfile);
	close_redir_fd(&utils->main_pipe[1]);
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
