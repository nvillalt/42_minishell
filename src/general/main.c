#include "../../minishell.h"

static int	create_new_shlvl(t_utils *utils)
{
	int		i;
	char	**new_env;

	i = 0;
	while(utils->env[i])
		i++;
	new_env = ft_calloc(i + 2, sizeof(char *));
	if (!new_env)
		return (0);
	i = 0;
	while(utils->env[i])
	{
		new_env[i] = ft_strdup(utils->env[i]);
		if (!new_env[i])
		{
			free_matrix(new_env);
			return (0);
		}
		i++;
	}
	new_env[i] = ft_strdup("SHLVL=1");
	if (!new_env[i])
	{
		free_matrix(new_env);
		return (0);
	}
	free_matrix(utils->env);
	utils->env = new_env;
	return (1);
}


static int	update_shlvl(t_utils *utils)
{
	int		i;
	int		new_lvl;
	char	*new_lvl_str;
	char	*shlvl;
	char	*new_shlvl;

	i = 0;
	while(utils->env[i] && ft_strncmp("SHLVL=", utils->env[i], 6))
		i++;
	if (!utils->env[i])
		return (create_new_shlvl(utils));
	shlvl = utils->env[i];
	i = 0;
	while(shlvl[i] && shlvl[i] != '=')
		i++;
	i++;
	if (!shlvl[i])
	{
		new_shlvl = ft_strdup("SHLVL=1");
		if (!new_shlvl)
			return (0);
		i = 0;
		while(utils->env[i] != shlvl)
			i++;
		free(utils->env[i]);
		utils->env[i] = new_shlvl;
		return (1);
}
	new_lvl = ft_atoi(shlvl + i) + 1;
	new_lvl_str = ft_itoa(new_lvl);
	if (!new_lvl_str)
		return (0);
	new_shlvl = ft_strjoin("SHLVL=", new_lvl_str);
	free(new_lvl_str);
	if (!new_shlvl)
		return (0);
	i = 0;
	while(utils->env[i] != shlvl)
		i++;
	free(utils->env[i]);
	utils->env[i] = new_shlvl;
	return (1);
}

static char	**create_mini_env(void)
{
	char	**env;
	char	*new_cwd;
	char	*join;
	char	*cwd;

	env = ft_calloc(4, sizeof(char *));
	if (!env)
	{
		ft_putendl_fd("minishell: Init error", STDOUT_FILENO);
		exit(1);
	}
	new_cwd = getcwd(NULL, 0);
	if (!new_cwd)
	{
		ft_putendl_fd("minishell: Init error", STDOUT_FILENO);
		free(env);
		exit (1); // AL LORO CON ESTAS LIBERACIONES 
	}
	env[0] = ft_strjoin("PWD=", new_cwd);
	free(new_cwd);
	if(!env[0])
	{
		ft_putendl_fd("minishell: Init error", STDOUT_FILENO);
		free(env);
		exit(1); // Controlar
	}
	env[1] = ft_strdup("SHLVL=1");
	if(!env[1])
	{
		ft_putendl_fd("minishell: Init error", STDOUT_FILENO);
		free_matrix(env);
		exit(1); //Controlar
	}
	env[2] = ft_strdup("_=/usr/bin/env");
	if(!env[2])
	{
		ft_putendl_fd("minishell: Init error", STDOUT_FILENO);
		free_matrix(env);
		exit(1); //Controlar
	}
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
	char	*temp;

	i = 0;
	while(env[i] && ft_strncmp_varlen("OLDPWD", env[i]))
		i++;
	if (env[i])
	{
		temp = ft_strdup("OLDPWD");
		if (!temp)
			return (NULL);
		free(env[i]);
		env[i] = temp;
		return (env);
	}
	else
	{
		new_env = ft_calloc(i + 2, sizeof(char *));
		if (!new_env)
			return (NULL);
		i = 0;
		while (env[i])
		{
			new_env[i] = ft_strdup(env[i]);
			if (!new_env[i])
				return (NULL);
			i++;
		}
		new_env[i] = ft_strdup("OLDPWD");
		if (!new_env[i])
			return (NULL);
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
		g_sigint = 0;
		utils->status = 0;
		set_signals();
		input = readline("minishell:");
		if (!input)
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
				utils->status = 1; //AL LORO CON EL NUMERO
			else
			{
				aux = trim_spaces(input);
				free(input);
				utils->status = get_tokens(aux, utils);
				if (utils->token_list != NULL)
				{
					expansor(utils);
					t_token *print = utils->token_list;
					while (print->next != NULL)
					{
						printf("Tokens en lista: %s\nExpande? %d\n", print->str, print->expand);
						print = print->next;
					}
					utils->status = parse_tokens(utils);
					printf("Tokens en lista: %s\nExpande? %d\n", print->str, print->expand);
					free(aux);
					executor(utils, utils->process);
					free_to_prompt(utils);
					if (utils->status == 130)
						printf("\n");
					else if (utils->status == 131)
						printf("Quit\n");
				}
			}
			printf("%d\n", utils->status);
		}
	}
	return (1);
}

int	g_sigint;

int	main(int argc, char **argv, char **envp)
{
	t_utils	utils;

	utils = init_utils();
	 if(!*envp)
	 	utils.env = create_mini_env();
	 else
	 {
		utils.env = env_dup(envp);
		if (!utils.env)
			exit(1);
		utils.path = get_path(utils.env);
		if (!utils.path)
		{
			free_matrix(utils.env);
			ft_putendl_fd("minishell: Init error", STDOUT_FILENO);
			exit(1);
		}
		if(!update_shlvl(&utils))
		{
			free_matrix(utils.env);
			free_matrix(utils.path);
			ft_putendl_fd("minishell: Init error", STDOUT_FILENO);
			exit(1);
		}
	}
	utils.env = set_oldpwd(utils.env);
	if (!utils.env)
	{
		free_matrix(utils.env);
		free_matrix(utils.path);
		ft_putendl_fd("minishell: Init error", STDOUT_FILENO);
		exit(1);
	}
	prompt_loop(&utils);
	free_utils(&utils);
	return (0);
}
