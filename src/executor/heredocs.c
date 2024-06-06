/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:52:14 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/06 17:22:11 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	write_here_doc(t_parse *process, t_utils *utils)
{
	char	*buffer;
	int		limiter_len;
	int		buffer_len;

	init_values_hd(&buffer, &limiter_len, &buffer_len, process);
	while (ft_strncmp_heredoc(buffer, process->redirec->doc, limiter_len)
		|| limiter_len != buffer_len)
	{
		buffer = init_buffer(buffer);
		if (!buffer)
			return (control_eof_hd(process, utils));
		if (g_sigint != 0)
			return (control_sigint_hd(buffer, utils));
		buffer = check_expansor_hd(process, buffer, utils);
		if (!buffer)
			return (0);
		buffer = append_newline(&buffer_len, buffer, utils);
		if (!buffer)
			return (FUNC_FAILURE);
		if (ft_strncmp_heredoc(buffer, process->redirec->doc, limiter_len)
			|| limiter_len != buffer_len)
			write(process->redirec->fd, buffer, buffer_len + 1);
	}
	return (free(buffer), FUNC_SUCCESS);
}

static int	exec_heredoc(t_utils *utils, t_parse *process, int *temp_num)
{
	if (!open_here_doc(process->redirec, temp_num))
	{
		utils->status = 1;
		return (FUNC_FAILURE);
	}
	if (!write_here_doc(process, utils))
		return (FUNC_FAILURE);
	utils->status = 0;
	return (FUNC_SUCCESS);
}

static int	create_heredoc_loop(t_parse *process, t_utils *utils)
{
	int	temp_num;

	temp_num = 1;
	while (process)
	{
		while (process->redirec)
		{
			if (process->redirec->redir_type == HEREDOC)
			{
				if (!exec_heredoc(utils, process, &temp_num))
					return (FUNC_FAILURE);
				temp_num++;
			}
			process->redirec = process->redirec->next;
		}
		process = process->next;
	}
	return (FUNC_SUCCESS);
}

int	create_multiple_heredocs(t_utils *utils, t_parse *process)
{
	heredoc_signals();
	if (!create_heredoc_loop(process, utils))
		return (FUNC_FAILURE);
	close_fds(process);
	set_signals();
	return (FUNC_SUCCESS);
}
