/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 18:48:54 by nvillalt          #+#    #+#             */
/*   Updated: 2024/06/06 18:56:27 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**create_mini_env(void)
{
	char	**env;
	char	*new_cwd;

	env = ft_calloc(4, sizeof(char *));
	if (!env)
		exit_init_void(NULL);
	new_cwd = getcwd(NULL, 0);
	if (!new_cwd)
		exit_init_void(env);
	env[0] = ft_strjoin("PWD=", new_cwd);
	free(new_cwd);
	if (!env[0])
		exit_init_void(env);
	env[1] = ft_strdup("SHLVL=1");
	if (!env[1])
		exit_init_void(env);
	env[2] = ft_strdup("_=./minishell");
	if (!env[2])
		exit_init_void(env);
	return (env);
}

t_utils	init_utils(void)
{
	t_utils	utils;

	utils.env = NULL;
	utils.path = NULL;
	utils.status = 0;
	utils.pid_array = NULL;
	utils.process = NULL;
	utils.token_list = NULL;
	utils.saved_stdin = -1;
	utils.saved_stdout = -1;
	return (utils);
}

int	handle_env(t_utils *utils, char **envp)
{
	utils->env = env_dup(envp);
	if (!utils->env)
		exit(1);
	if (!update_shlvl(utils))
		exit_init_void(utils->env);
	return (1);
}
