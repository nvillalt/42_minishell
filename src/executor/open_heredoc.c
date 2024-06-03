/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:54:45 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/03 16:55:28 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	get_file_name(t_redir *redirec, int temp_num)
{
	char	*str_num;

	str_num = ft_itoa(temp_num);
	if (!str_num)
	{
		perror("minishell");
		return (FUNC_FAILURE);
	}
	redirec->heredoc_file = ft_strjoin("/tmp/.temp", str_num);
	free(str_num);
	if (!redirec->heredoc_file)
	{
		perror("minishell");
		return (FUNC_FAILURE);
	}
	return (FUNC_SUCCESS);
}

int	open_here_doc(t_redir *redirec, int *temp_num)
{
	if (!get_file_name(redirec, *temp_num))
		return (FUNC_FAILURE);
	while (access(redirec->heredoc_file, F_OK) == 0)
	{
		++*temp_num;
		free(redirec->heredoc_file);
		if (!get_file_name(redirec, *temp_num))
			return (FUNC_FAILURE);
	}
	redirec->fd = open(redirec->heredoc_file,
			O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (redirec->fd == -1)
		return (ft_puterror(redirec->doc));
	return (FUNC_SUCCESS);
}
