/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:39:26 by nvillalt          #+#    #+#             */
/*   Updated: 2024/06/06 18:57:42 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	g_sigint;

static void	exec_shell(t_utils *utils, char *input)
{
	char	*aux;

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
			if (parse_tokens(utils))
			{
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

static int	prompt_loop(t_utils *utils)
{
	char	*input;

	while (1)
	{
		g_sigint = 0;
		utils->parent_builtin = 0;
		set_signals();
		input = readline("minishell:");
		if (!input)
			ctrl_d_signal_exit(utils);
		if (!*input)
			free(input);
		else
			exec_shell(utils, input);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_utils	utils;

	if (argc != 1 || argv[1] != NULL)
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
		exit_init_void(utils.env);
	prompt_loop(&utils);
	free_utils(&utils);
	return (0);
}
