/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:47:03 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/03 18:51:30 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	exec_sigint(int signal)
{
	write(STDERR_FILENO, "\n", 0);
	if (signal == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", -1);
		rl_redisplay();
	}
}

void	set_signals(void)
{
	signal(SIGINT, exec_sigint);
	signal(SIGQUIT, SIG_IGN);
}
