/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:34:25 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/06 17:21:12 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	control_eof_hd(t_parse *process, t_utils *utils)
{
	close_fds(process);
	ft_putstr_fd("minishell:", STDERR_FILENO);
	ft_putendl_fd(EOFERR, STDERR_FILENO);
	utils->status = 0;
	return (1);
}

int	control_sigint_hd(char *buffer, t_utils *utils)
{
	free(buffer);
	utils->status = 130;
	return (0);
}

void	init_values_hd(char **buffer, int *limiter_len,
	int *buffer_len, t_parse *process)
{
	*buffer = NULL;
	*buffer_len = 0;
	*limiter_len = ft_strlen(process->redirec->doc);
}

char	*init_buffer(char *buffer)
{
	if (buffer)
		free(buffer);
	buffer = readline("> ");
	return (buffer);
}
