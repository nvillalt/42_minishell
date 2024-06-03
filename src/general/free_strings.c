/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_strings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:28:44 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/03 17:28:45 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**free_str_matrix(char *str, char **matrix)
{
	if (str)
		free(str);
	if (matrix)
		free_matrix(matrix);
	perror("minishell");
	return (NULL);
}
