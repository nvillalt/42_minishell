#include "../../minishell.h"

static char	*get_bef_exp_str(char *buffer, int i)
{
	int		bef_exp_len;
	char	*bef_exp;

	bef_exp_len = i;
	bef_exp = ft_substr(buffer, 0, bef_exp_len);
	if (!bef_exp)
	{
		free(buffer);
		perror("minishell");
		return (NULL);
	}
	return (bef_exp);
}

static char	*get_aft_exp_str(char *buffer, int i, char *key, char *bef_exp)
{
	int		aft_exp_len;
	int		bef_exp_len;
	int		key_len;
	int		dollar_len;
	char	*after_exp;

	dollar_len = 0;
	while(buffer[i] && buffer[i] == '$')
	{
		i++;
		dollar_len++;
	}
	bef_exp_len = ft_strlen(bef_exp);
	key_len = ft_strlen(key);
	aft_exp_len = ft_strlen(buffer) - (bef_exp_len + key_len + 1);
	after_exp = ft_substr(buffer, bef_exp_len + key_len + dollar_len, aft_exp_len);
	if (!after_exp)
	{
		free(buffer);
		perror("minishell");
		return (NULL);
	}
	return (after_exp);
}

static char	*get_new_buffer(char *val, char *bef_exp, char *after_exp)
{
	char	*new_buffer;
	char	*temp;

	if (!val)
	{
		new_buffer = ft_strjoin_hd(bef_exp, after_exp);
		if (!new_buffer)
			return(free_puterror(NULL, NULL, NULL, 0));
		return (new_buffer);
	}
	temp = ft_strjoin_hd(bef_exp, val);
	if (!temp)
		return(free_puterror(NULL, NULL, NULL, 0));
	new_buffer = ft_strjoin_hd(temp, after_exp);
	free(temp);
	if (!new_buffer)
		return (free_puterror(NULL, NULL, NULL, 0));
	return (new_buffer);
}

static char	*create_new_buffer(char *buffer, char *val, char *key, int *i)
{
	char	*new_buffer;
	char	*bef_exp;
	char	*after_exp;
	char	*temp;

	bef_exp = get_bef_exp_str(buffer, *i);
	if (!bef_exp)
		return (NULL);
	after_exp = get_aft_exp_str(buffer, *i, key, bef_exp);
	if (!after_exp)
	{
		if (bef_exp)
			free(bef_exp);
		return (NULL);
	}
	new_buffer = get_new_buffer(val, bef_exp, after_exp);
	free(buffer);
	if (bef_exp)
		free(bef_exp);
	free(after_exp);
	if (!new_buffer)
		return (NULL);
	if (val)
		*i += ft_strlen(val);
	return (new_buffer);
}

static void	free_ptrs(void *ptr1, void *ptr2)
{
	if (ptr1)
		free(ptr1);
	if (ptr2)
		free(ptr2);
}

static char	*updt_status_return(t_utils *utils, int status)
{
	utils->status = status;
	return (NULL);
}

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
