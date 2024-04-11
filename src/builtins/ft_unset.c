#include "../../minishell.h"

static char **allocate_memory(char **dup, char **env, int index_jump)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(env[i] != NULL)
	{
		if (i == index_jump)
			i++;
		dup[j] = ft_strdup(env[i]);
		if (!dup[j])
		{
			perror(NULL);
			free_matrix(dup);
			exit(1);
		}
		i++;
		j++;
	}
	return (dup);
}

static char	**create_new_env(char **env, int index_jump)
{
	char	**dup;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (env[i] != NULL)
		i++;
	dup = ft_calloc(sizeof(char *), i); //NO SUMAMOS 1 PORQUE EN REALIDAD VAMOS A SALTARNOS UNA LÍNEA
	if (!dup)
	{
		free(env);
		perror(NULL);
		exit(1); //TOCARÁ LIBERAR MÁS COSAS. OJO CON EL VALOR DE SALIDA
	}
	i = 0;
	j = 0;
	dup = allocate_memory(dup, env, index_jump);
	return (dup);
}

static char **search_for_var(char **env, char *current_var)
{
    size_t	i;
    size_t	index_jump;
    int		var_len;
	char	**new_env;
	char	*join_var;

    index_jump = 0;
    i = 0;
	new_env = NULL;
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
	if (!env[i])
	{
		new_env = env_dup(env);
		if (!new_env)
		{
			perror(NULL);
			exit (1);
		}
		return(new_env);
	}
	index_jump = i;
	new_env = create_new_env(env, index_jump);
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