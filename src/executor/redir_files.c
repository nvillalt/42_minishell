/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:46:29 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/05 17:10:38 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	redirec_infile(int last_infile, t_utils *utils)
{
	if (last_infile >= 0)
	{
		if (dup2(last_infile, STDIN_FILENO))
		{
			perror("minishell");
			if (utils->parent_builtin == 1)
				return (FUNC_FAILURE);
			else
				exit_process(utils);
		}
	}
	return (FUNC_SUCCESS);
}
int	redirec_outfile(int last_outfile, t_utils *utils)
{
	if (last_outfile >= 0)
	{
		if (dup2(last_outfile, STDOUT_FILENO) == -1)
		{
			perror("minishell");
			if (utils->parent_builtin == 1)
				return (FUNC_FAILURE);
			else
				exit_process(utils);
		}
	}
	return (FUNC_SUCCESS);
}
