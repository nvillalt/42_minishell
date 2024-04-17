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

static int	search_for_set_var(char **env, char *current_var)
{
	int		i;
	char	*join_var;
	int		var_len;;

	i = 0;
	join_var = ft_strjoin(current_var, "=");
	if (!join_var)
	{
		perror(NULL);
		exit(1); //ESTO HAY QUE TOCARLO CORRECTAMENTE
	}
    var_len = ft_strlen(join_var);
	while(env[i] && ft_strncmp(env[i], join_var, var_len))
        i++;
	free(join_var);
	return (i);
}

static char **search_for_var(char **env, char *current_var)
{
    int		index_jump;
	char	**new_env;

	index_jump = search_for_set_var(env, current_var);
	if (!env[index_jump])
	{
		index_jump = search_empty_var(env, current_var);
		if (index_jump == -1)
			return(env);
	}
	new_env = unset_var_env(env, index_jump);
	return (new_env);
}

char	**ft_unset(char **env, char **var)
{
    int     index_var;
    char    **new_env;
	char	**old_env;

	if (!env || !var[1])
		return (NULL);
    index_var = 1;
    new_env = NULL;
	old_env = env;
    while(var[index_var])
    {
		new_env = search_for_var(old_env, var[index_var]);
		free_matrix(old_env);
		old_env = new_env;
		index_var++;
    }
	return (new_env);
}