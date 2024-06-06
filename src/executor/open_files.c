/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:29:47 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/06 17:23:32 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	open_files(t_utils *utils, t_parse *process,
	int *last_infile, int *last_outfile)
{
	while (process->redirec)
	{
		if (process->redirec->redir_type == MINUS
			|| process->redirec->redir_type == HEREDOC)
		{
			open_infiles(process, utils, last_infile);
			if (*last_infile == -2)
				return ;
		}
		else if (process->redirec->redir_type == GREAT
			|| process->redirec->redir_type == APPEND)
		{
			open_outfiles(process, utils, last_outfile);
			if (*last_outfile == -2)
				return ;
		}
		process->redirec = process->redirec->next;
	}
}
