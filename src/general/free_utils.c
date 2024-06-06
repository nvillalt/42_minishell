/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:28:55 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/06 18:57:32 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	return ;
}

void	free_parse_list(t_parse	*process)
{
	t_parse	*temp;
	t_redir	*redir_temp;

	while (process)
	{
		if (process->cmd)
			free_matrix(process->cmd);
		process->redirec = process->redirec_head;
		while (process->redirec)
		{
			redir_temp = process->redirec;
			if (process->redirec->doc)
				free(process->redirec->doc);
			if (process->redirec->heredoc_file)
				free(process->redirec->heredoc_file);
			process->redirec = process->redirec->next;
			free(redir_temp);
		}
		temp = process;
		process = process->next;
		free(temp);
	}
}

void	free_utils(t_utils *utils)
{
	if (utils->env)
		free_matrix(utils->env);
	if (utils->path)
		free_matrix(utils->path);
	if (utils->process)
		free_lists(utils);
	if (utils->pid_array)
		free(utils->pid_array);
}

void	free_lists(t_utils	*utils)
{
	if (utils->process)
	{
		free_parse_list(utils->process);
		utils->process = NULL;
	}
	if (utils->pid_array)
	{
		free(utils->pid_array);
		utils->pid_array = NULL;
	}
}

void	ctrl_d_signal_exit(t_utils *utils)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	exit_process_custom(utils, 0);
	exit (0);
}
