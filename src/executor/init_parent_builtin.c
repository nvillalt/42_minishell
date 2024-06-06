/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parent_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:02:10 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/06 15:08:06 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_parent_builtin(t_utils *utils, int *last_infile, int *last_outfile)
{
	*last_infile = -1;
	*last_outfile = -1;
	utils->parent_builtin = 1;
}
