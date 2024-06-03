/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:36:47 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/03 15:38:08 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	control_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	if (i == 1)
		return (1);
	else
		return (0);
}

static int	equal_in_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	ft_env(char **env, char **argv)
{
	int	i;

	i = 0;
	if (!env)
	{
		ft_putendl_fd ("minishell: env: No such file or directory", 2);
		return (127);
	}
	if (!control_argv(argv))
	{
		ft_putstr_fd ("env: ", STDERR_FILENO);
		ft_putstr_fd ("\'", STDERR_FILENO);
		ft_putstr_fd (argv[1], STDERR_FILENO);
		ft_putstr_fd ("\': ", STDERR_FILENO);
		ft_putendl_fd ("No such file or directory", STDERR_FILENO);
		return (127);
	}
	while (env[i])
	{
		if (equal_in_str(env[i]))
			printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
