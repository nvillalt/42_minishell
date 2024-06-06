/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_infiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:39:23 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/06 14:09:53 by fmoran-m         ###   ########.fr       */
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

void	open_infiles(t_parse *process, t_utils *utils, int *last_infile)
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
}
