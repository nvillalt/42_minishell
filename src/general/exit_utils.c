/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:24:19 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/04 12:33:38 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exit_matrix_str(char *str, char **matrix,
	char *error_str, t_utils *utils)
{
	if (str)
		free(str);
	if (matrix)
		free(matrix);
	perror(error_str);
	exit_process(utils);
}

void	exit_process_path(t_utils *utils, t_parse *process, int status)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(process->cmd[0]);
	exit_process_custom(utils, status);
}

int	change_status(t_utils *utils, int status)
{
	utils->status = 1;
	return (FUNC_FAILURE);
}

void	exit_init_void(char **matrix)
{
	if (matrix)
		free_matrix(matrix);
	ft_putendl_fd("minishell: Init error", STDOUT_FILENO);
	exit (1);
}

int	free_matrix_return(char **matrix)
{
	free_matrix(matrix);
	return (0);
}
