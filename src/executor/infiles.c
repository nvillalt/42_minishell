/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infiles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:53:53 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/03 16:54:34 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	open_minus(int last_infile_fd, t_utils *utils, t_parse *process)
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
	last_infile_fd = process->redirec->fd;
	return (last_infile_fd);
}

static int	open_heredoc(int last_infile_fd, t_utils *utils, t_parse *process)
{
	process->redirec->fd = open(process->redirec->heredoc_file, O_RDONLY);
	if (process->redirec->fd == -1)
	{
		ft_puterror(process->redirec->doc);
		if (utils->parent_builtin == 1)
			return (FUNC_FAILURE);
		else
			exit_process(utils);
	}
	last_infile_fd = process->redirec->fd;
	return (last_infile_fd);
}

static int	open_infiles(t_utils *utils, t_parse *process)
{
	int	last_infile_fd;

	last_infile_fd = -1;
	process->redirec = process->redirec_head;
	while (process->redirec)
	{
		if (process->redirec->redir_type == MINUS)
			last_infile_fd = open_minus(last_infile_fd, utils, process);
		if (process->redirec->redir_type == HEREDOC)
			last_infile_fd = open_heredoc(last_infile_fd, utils, process);
		process->redirec = process->redirec->next;
	}
	return (last_infile_fd);
}

int	redirec_infile(t_utils *utils, t_parse *process)
{
	int	last_infile_fd;

	last_infile_fd = open_infiles(utils, process);
	if (last_infile_fd == -1)
		return (FUNC_FAILURE);
	if (last_infile_fd == -2)
		return (-2);
	if (dup2(last_infile_fd, STDIN_FILENO) == -1)
	{
		perror("minishell");
		if (utils->parent_builtin == 1)
			return (-2);
		else
			exit_process(utils);
	}
	close_fds(utils->process, utils);
	return (FUNC_SUCCESS);
}
