#include "../../minishell.h"

static char	**create_mini_env(void)
{
	char	**env;
	char	*new_cwd;
	char	*join;
	char	*cwd;

	env = ft_calloc(4, sizeof(char *));
	new_cwd = getcwd(NULL, 0);
	if (!new_cwd)
		exit (1); // AL LORO CON ESTAS LIBERACIONES 
	env[0] = ft_strjoin("PWD=", new_cwd);
	free(new_cwd);
	if(!env[0])
		exit(1); // Controlar
	env[1] = ft_strdup("SHLVL=1");
	if(!env[1])
		exit(1); //Controlar
	env[2] = ft_strdup("_=/usr/bin/env");
	if(!env[2])
		exit(1); //Controlar
	return (env);
}

static int	ft_strncmp_varlen(char *cmd, char *env_line)
{
	int	cmd_len;
	int	var_len;

	cmd_len = ft_strlen(cmd);
	var_len = 0;
	while(env_line[var_len] && env_line[var_len] != '=')
		var_len++;
	if (ft_strncmp(cmd, env_line, cmd_len) == 0 && cmd_len == var_len)
		return(0);
	else	
		return (1);
}

static char	**set_oldpwd(char **env)
{
	int		i;
	char	**new_env;

	i = 0;
	while(env[i] && ft_strncmp_varlen("OLDPWD", env[i]))
		i++;
	if (env[i])
	{
		free(env[i]);
		env[i] = ft_strdup("OLDPWD");
		return (env);
	}
	else
	{
		new_env = ft_calloc(i + 2, sizeof(char *));
		i = 0;
		while (env[i])
		{
			new_env[i] = ft_strdup(env[i]);
			if (!new_env[i])
			{
				perror(NULL);
				exit(1);
			}
			i++;
		}
		new_env[i] = ft_strdup("OLDPWD");
		free_matrix(env);
		return(new_env);
	}
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
	return (utils);
}

int	prompt_loop(t_utils *utils)
{
	char	*input;
	char	*aux;
	
	while (1)
	{
		input = readline("minishell:");
		if (!input) // Saltar la linea en blanco;
		{
			printf("exit\n");
			free_matrix(utils->env);
			free_matrix(utils->path);
			exit (0);
		}
		if (!*input)
			free(input);
		else
		{
			add_history(input);
			if (!check_quotes(input, utils) || !initial_pipe(input, utils))
				utils->status = 130;
			else
			{
				aux = trim_spaces(input);
				free(input);
				utils->status = get_tokens(aux, utils);
				free(aux);
				t_token	*print;

				print = utils->token_list;
				printf("print: %s\n", print->str);
				while (print->next != NULL)
				{
					print = print->next;
					printf("print: %s\n", print->str);
				}
				utils->status = parse_tokens(utils);
			}
			printf("%d\n", utils->status);
		}
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_utils	utils;

	utils = init_utils();
	if(!*envp)
		utils.env = create_mini_env();
	else
	{
		utils.env = env_dup(envp); // Aquí se aloja memoria. Liberarla más adelante.
		utils.path = get_path(utils.env);
	}
	utils.env = set_oldpwd(utils.env);
	//set_signals();
	prompt_loop(&utils);
	free_utils(&utils);
	return (0);
}
