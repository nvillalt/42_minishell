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
			return (free_matrix_return(new_env));
		i++;
	}
	new_env[i] = ft_strdup("SHLVL=1");
	if (!new_env[i])
		return (free_matrix_return(new_env));
	free_matrix(utils->env);
	utils->env = new_env;
	return (1);
}

static int	set_unassigned_shlvl(t_utils *utils, char *shlvl, int i)
{
	char	*new_shlvl;

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

static int	increment_shlvl(t_utils *utils, char *shlvl, int i)
{
	int		new_lvl;
	char	*new_shlvl;
	char	*new_lvl_str;	

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

int	update_shlvl(t_utils *utils)
{
	int		i;
	char	*shlvl;

	i = 0;
	while(utils->env[i] && ft_strncmp_varlen("SHLVL", utils->env[i]))
		i++;
	if (!utils->env[i])
		return (create_new_shlvl(utils));
	shlvl = utils->env[i];
	i = 0;
	while(shlvl[i] && shlvl[i] != '=')
		i++;
	i++;
	if (!shlvl[i])
		return(set_unassigned_shlvl(utils, shlvl, i));
	else
		return(increment_shlvl(utils, shlvl, i));
}