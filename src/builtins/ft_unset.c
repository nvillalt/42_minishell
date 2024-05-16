#include "../../minishell.h"

static int	search_empty_var(char **env, char *current_var)
{
	int	i;
	int	var_len;

	i = 0;
	var_len = ft_strlen(current_var);
	while (env[i] && ft_strncmp(env[i], current_var, var_len))
		i++;
	if (!env[i])
		return(-1);
	else
		return(i);
}

static int	search_for_set_var(char **env, char *current_var, int *index_jump)
{
	char	*join_var;
	int		var_len;;

	join_var = ft_strjoin(current_var, "=");
	if (!join_var)
	{
		perror("minishell");
		free_matrix(env);
		return (FUNC_FAILURE);
	}
    var_len = ft_strlen(join_var);
	while(env[*index_jump] && ft_strncmp(env[*index_jump], join_var, var_len))
		(*index_jump)++; //AQUÍ PUEDE ESTAR EL ERROR
	free(join_var);
	return (FUNC_SUCCESS);
}

static char **search_for_var(char **env, char *current_var)
{
    int		index_jump;
	char	**new_env;

	index_jump = 0;
	if (!search_for_set_var(env, current_var, &index_jump))
		return (NULL);
	if (!env[index_jump]) // SI NO ENCUENTRA LA VARIABLE
	{
		index_jump = search_empty_var(env, current_var);
		if (index_jump == -1)
		{
			new_env = env_dup(env);
			if (!new_env)
				return (NULL);
			return(new_env);
		}
	}
	new_env = unset_var_env(env, index_jump);
	if (!new_env)
		return (NULL);
	return (new_env);
}

int	ft_unset(t_utils *utils, char **cmd)
{
    int     index_var;
    char    **new_env;
	char	**old_env;

	if (!cmd[1])
		return (0);
	old_env = env_dup(utils->env);
	if (!old_env)
	{
		perror("minishell");
		return (1);
	}
    index_var = 1;
    new_env = NULL;
    while(cmd[index_var])
    {
		new_env = search_for_var(old_env, cmd[index_var]);
		if (!new_env)
			return (1);
		free_matrix(old_env);
		old_env = new_env;
		index_var++;
	}
	free_matrix(utils->env);
	utils->env = old_env;
	return (0);
}