#include "../../minishell.h"

int	get_val_from_env(char **env, char *key, char **val)
{
	*val = ft_getenv(env, key);
	if (*val)
	{
		*val = ft_strdup(*val);
		if (!*val)
			return (0);
	}
	return (1);
}

static char	*update_buffer(char *buffer, char **env, t_utils *utils, int i)
{
	int		j;
	char	*val;
	char	*key;

	key = get_keyhd(buffer, i, utils);
	if (!key)
		return (NULL);
	if  (*key == '$')
	{
		val = ft_strdup(key);
		if (!val)
			return(free_puterror(NULL, key, utils, 1));
	}
	else
	{
		if (!get_val_from_env(env, key, &val))
			return (free_puterror(NULL, key, utils, 1));
		buffer = create_new_buffer(buffer, val, key, &i);
		if (!buffer)
			return(updt_status_return(utils, 1));
	}
	free_ptrs(key, val);
	return (buffer);
}

static char	*expand_heredoc(char *buffer, char **env, t_utils *utils)
{
	int		i;
	int		j;

	i = 0;
	while (buffer[i])
	{
		j = i;
		if (buffer[i] == '$')
		{
			buffer = update_buffer(buffer, env, utils, i);
			if (!buffer)
				return (NULL);
		}
		if (i == j)
			i++;
	}
	return (buffer);
}

char	*get_keyhd(char *buffer, int i, t_utils *utils)
{
	int		start;
	char	*key;

	while(buffer[i] && buffer[i] == '$')
		i++;
	i--;
	start = i + 1;
	i++;
	while (buffer[i] && ft_isalnum(buffer[i]))
		i++;
	if (start == i)
    {
        key = ft_strdup("$");
        if (!key)
            return (free_puterror(NULL, NULL, utils, 1));
    }
	key = ft_substr(buffer, start, i - start);
	if (!key)
        return (free_puterror(NULL, NULL, utils, 1));
	return (key);
}

char	*check_expansor_hd(t_parse *process, char *buffer, t_utils *utils)
{
	if (process->redirec->heredoc_flag == EXPAND)
	{
		buffer = expand_heredoc(buffer, utils->env, utils);
		if (!buffer)
			return (NULL);
	}
	return (buffer);
}
