/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_frees.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:23:54 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/06 17:22:04 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_to_prompt(t_utils *utils)
{
	unlink_files(utils->process);
	close_all_redirs(utils);
	close_fds(utils->process);
	free_lists(utils);
}

void	exit_process(t_utils *utils)
{
	close_all_redirs(utils);
	close_fds(utils->process);
	free_utils(utils);
	exit(EXIT_FAILURE);
}

void	exit_process_noerror(t_utils *utils)
{
	close_all_redirs(utils);
	close_fds(utils->process);
	free_utils(utils);
	exit(EXIT_SUCCESS);
}

void	exit_process_custom(t_utils *utils, unsigned char status)
{
	close_all_redirs(utils);
	close_fds(utils->process);
	free_utils(utils);
	rl_clear_history();
	exit(status);
}
