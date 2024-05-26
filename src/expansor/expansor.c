#include "../../minishell.h"

static int	check_valid_symbol(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '$' && str[i])
		i++;
	if (str[i] == '$' && str[i + 1] == '?')
		return (1);
	if (str[i] == '$')
	{
		if (ft_isdigit(str[i + 1]))
			return (0);
		while (str[i])
		{
			if (str[i] == '$' && str[i + 1] == '$')
				return (0);
			if (str[i] == '-' || str[i] == '!' || str[i] == '?'
				|| str[i] == '\\' || str[i] == '/' ||str[i] == '('
				|| str[i] == ')')
				return (0);
			i++;
		}
	}
	return (1);
}

static char	*expand_env(char *var, char **env)
{
	int		i;
	int		len;
	int		env_len;

	i = 0;
	len = ft_strlen(var);
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
			env_len = ft_strlen(ft_strchr(env[i], '=')) - ft_strlen(env[i]);
		if (env_len < 0)
			env_len *= -1;
		if (!ft_strncmp(var, env[i], env_len) && (env_len == len))
		{
			if (ft_strchr(env[i], '=') == NULL)
				return (ft_strdup(""));
			else if (ft_strchr(env[i], '=') != NULL)
				return(ft_strdup(ft_strchr(env[i], '=') +  1));
			break ;
		}
		i++;
	}
	return (ft_strdup(""));
}

static int	get_mid(char *str, int i, char **s2, int st, char **env)
{
	char	*tmp;
	int		j;

	if (str[i] == '$' && str[i + 1] == '?')
	{
		*s2 = ft_itoa(st);
		return (2);
	}
	else if (str[i] == '$' && str[i + 1] == '\0')
	{
		*s2 = ft_strdup("$");
		return (1);
	}
	else if (str[i] == '$')
		i++;
	j = i;
	while (ft_isalnum(str[i]))
		i++;
	tmp = ft_substr(str, j, i - j);
	*s2 = expand_env(tmp, env);
	free(tmp);
	return (i);
}

static int	get_beginning(char *str, int i, char **s1)
{
	if (str[0] == '$')
		*s1 = ft_strdup("");
	else if (str[0] != '$')
	{
		while (str[i] != '$')
			i++;
		*s1 = ft_substr(str, 0, i);
	}
	return (i);
}

static int	get_end(char *str, int i, char **s1)
{
	int	j;

	j = i;
	if (str[i] == '\0')
		*s1 = ft_strdup("");
	else if (str[i] != '\0')
	{
		while (str[i] != '\0')
			i++;
		*s1 = ft_substr(str, j, i - j);
	}
	return (i);
}

static char	*var_expanded(char *str, char **env, int status)
{
	char	*s1;
	char	*s2;
	char	*ret;
	int		i;

	s1 = NULL;
	s2 = NULL;
	ret = NULL;
	i = 0;
	i = get_beginning(str, i, &s1);
	i = get_mid(str, i, &s2, status, env);
	ret = ft_strjoin(s1, s2);
	if (s1 != NULL)
		free(s1);
	if (s2)
		free(s2);
	i = get_end(str, i, &s1);
	s2 = ft_strjoin(ret, s1);
	if (ret)
		free(ret);
	if (s1)
		free(s1);
	free(str);
	return (s2);
}

static char	*expand_env_var(char *str, char **env, int status)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == 34 && !flag)
		{
			flag = str[i];
			i++;
			while (str[i] != flag)
				i++;
			flag = 0;
		}
		else if (str[i] == 39 && !flag)
		{
			flag = str[i];
			i++;
			while (str[i] != flag)
			{
				if (str[i] =='$')
					return (str);
				i++;
			}
			flag = 0;
		}
		i++;
	}
	return (var_expanded(str, env, status));
}

static int	check_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

static int	check_valid_redir(char *s1, t_token *tmp, t_utils *utils)
{
	if (s1 != NULL && tmp != NULL)
	{
		if ((!ft_strncmp(s1, ">>", 2) && !ft_strncmp(tmp->str, "<<", 2))
			|| !ft_strncmp(s1, ">", 1) && !ft_strncmp(tmp->str, "<", 1)
			|| !ft_strncmp(s1, ">", 1) && !ft_strncmp(tmp->str, ">", 1))
		{
			ft_putendl_fd("syntax error near unexpected token `>>'", 2);
			utils->status = 2;
			return (0);
		}
		else if (!ft_strncmp(s1, "<<", 2) && !ft_strncmp(tmp->str, ">>", 2)
			|| !ft_strncmp(s1, "<", 1) && !ft_strncmp(tmp->str, ">", 1)
			|| !ft_strncmp(s1, "<", 1) && !ft_strncmp(tmp->str, "<", 1))
		{
			ft_putendl_fd("syntax error near unexpected token `<<'", 2);
			utils->status = 2;
			return (0);
		}
	}
	return (1);
}

int	expansor(t_utils *utils)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = utils->token_list;
	while (tmp->str)
	{
		if (!check_valid_redir(tmp->str, tmp->next, utils))
		{
			clear_token_list(&utils->token_list);
			return (0);
		}
		if (check_valid_symbol(tmp->str) && check_dollar(tmp->str))
		{
			tmp->str = expand_env_var(tmp->str, utils->env, utils->status);
		}
		if (tmp->str && tmp->next == NULL)
			break ;
		if (tmp->str)
			tmp = tmp->next;
	}
	return (1);
}
