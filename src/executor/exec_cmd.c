/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:20:15 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/06 17:21:19 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exec_cmd(t_utils *utils, t_parse *current_process)
{
	char	*path;

	path = get_cmd_path(utils, current_process);
	if (execve(path, current_process->cmd, utils->env) == -1)
	{
		ft_putstr_fd(current_process->cmd[0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		close_fds(utils->process);
		free_utils(utils);
		exit(127);
	}
}
