/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:39:26 by nvillalt          #+#    #+#             */
/*   Updated: 2024/06/06 17:24:18 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	g_sigint;

static char	**create_mini_env(void)
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
	if(!env[0])
		exit_init_void(env);
	env[1] = ft_strdup("SHLVL=1");
	if(!env[1])
		exit_init_void(env);
	env[2] = ft_strdup("_=./minishell");
	if(!env[2])
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

int	prompt_loop(t_utils *utils)
{
	char	*input;
	char	*aux;
	
	while (1)
	{
		g_sigint = 0;
		utils->parent_builtin = 0;
		set_signals();
		input = readline("minishell:");
		if (!input)
		{
			ft_putendl_fd("exit", STDERR_FILENO);
			exit_process_custom(utils, 0);
			exit (0);
		}
		if (!*input)
			free(input);
		else
		{
			add_history(input);
			if (!check_quotes(input, utils) || !initial_pipe(input, utils)
				|| !syntax_error(input, utils))
				free(input);
			else
			{
				aux = trim_spaces(input);
				free(input);
				get_tokens(aux, utils);
				free(aux);
				if (utils->token_list != NULL && expansor(utils))
				{
					parse_tokens(utils);
					executor(utils, utils->process);
					free_to_prompt(utils);
					if (utils->status == 130 && g_sigint == 0)
						printf("\n");
					else if (utils->status == 131)
						printf("Quit\n");
				}
			}
		}
	}
	return (1);
}

static int handle_env(t_utils *utils, char **envp)
{
	utils->env = env_dup(envp);
	if (!utils->env)
		exit(1);
	if(!update_shlvl(utils))
	{
		free_matrix(utils->env);
		ft_putendl_fd("minishell: Init error", STDOUT_FILENO);
		exit(1);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_utils	utils;

	if (argc != 1 || argv[argc] != NULL)
	{
		ft_putendl_fd("error: execute without arguments", STDERR_FILENO);
		return (1);
	}
	utils = init_utils();
	if (!*envp)
	 	utils.env = create_mini_env();
	else
		handle_env(&utils, envp);
	utils.env = set_oldpwd(utils.env);
	if (!utils.env)
	{
		free_matrix(utils.env);
		ft_putendl_fd("minishell: Init error", STDOUT_FILENO);
		exit(1);
	}
	prompt_loop(&utils);
	free_utils(&utils); //esto creo que no toca
	return (0);
}
