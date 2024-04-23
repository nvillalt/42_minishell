#include "../../minishell.h"

static char	**create_mini_env(void)
{
	char	**env;
	char	*new_cwd;
	char	*join;
	char	cwd[PATH_MAX + 1];

	env = ft_calloc(4, sizeof(char *));
	new_cwd = getcwd(new_cwd, PATH_MAX);
	env[0] = ft_strjoin("PWD=", new_cwd);
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

int	prompt_loop(t_utils *utils)
{
	char	*input;
	char	*aux;
	
	while (1)
	{
		input = readline("minishell:");
		if (!*input) // Saltar la linea en blanco
			free(input);
		else
		{
			add_history(input);
			if (!check_quotes(input) || !initial_pipe(input))
				printf("ERROR\n"); // Liberación aquí o exit por error
			dirty_parse(input, utils);
			executor(utils);
			//aux = trim_spaces(input); // hace substr de esto para empezar a limpiar la string
			//free(input);
			//clean_tokens(utils, aux);
			//free_utils(utils);
		}
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_utils	utils;

	utils.status = 0;
	if(!*envp)
		utils.env = create_mini_env();
	else
	{
		utils.env = env_dup(envp); // Aquí se aloja memoria. Liberarla más adelante.
		utils.path = get_path(utils.env);
	}
	utils.env = set_oldpwd(utils.env);
	prompt_loop(&utils);
	free_utils(&utils);
	return (0);
}

