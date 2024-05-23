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
static int	count_var(char *str)
{
	int	len;

	len = ft_strlen(str);
	while (str[len - 1])
	{
		if (str[len - 1] == 34 || str[len - 1] == 39)
		{
			while (str[len - 1] == 34 || str[len - 1] == 39)
				len--;
		}
		if (ft_isalpha(str[len - 1]) && !ft_isalpha(str[len - 2]))
		{
			len -= 2;
			break ;
		}
		len--;
	}
	if (len == 1 && str[len - 1] == '$')
		return (ft_strlen(str));
	return (len - 1);
}

static char	*expansion(char *str, int i, char **env, int st)
{
	
}

// static char	*expansion(char *str, int i, char **env, int st)
// {
// 	int		len;
// 	char	*var;
// 	char	*tmp;
// 	int		j;
// 	int		env_var;

// 	j = 0;
// 	if (str[i] == '$' && str[i + 1] == '?')
// 		tmp = ft_itoa(st);
// 	else
// 	{
// 		len = count_var(str + i);
// 		var = ft_substr(str, i + 1, len);
// 		i += ft_strlen(var);
// 		printf("VAR: %s\n", var);
// 		while (env[j] != NULL)
// 		{
// 			if (ft_strchr(env[j], '='))
// 				env_var = ft_strlen(ft_strchr(env[j], '=')) - ft_strlen(env[j]);
// 			if (env_var < 0)
// 				env_var *= -1;
// 			if (!ft_strncmp(var, env[j], env_var))
// 			{
// 				printf("COMP: %d\n", ft_strncmp(var, env[j], env_var));
// 				free(var);
// 				if (ft_strchr(env[j], '=') == NULL)
// 					var = ft_strdup("");
// 				else if (ft_strchr(env[j], '=') != NULL)
// 					var = ft_strdup(ft_strchr(env[j], '=') + 1);
// 				break ;
// 			}
// 			j++;
// 		}
// 	}
// 	if (str[i + 1] == '\0')
// 		return (var);
// 	else
// 	{
// 		tmp = ft_substr(str, i + 1, len);
// 		free(str);
// 		str = ft_strjoin(var, tmp);
// 		if (var)
// 			free(var);
// 		free(tmp);
// 	}
// 	return (str);
// }

static char	*var_expanded(char *str, char **env, int status)
{
	int		i;
	char	*aux;
	char	*tmp;
	char	*ret;

	i = 0;
	if (str[0] == '$' && str[1] == '?')
	{
		free(str);
		return (ft_itoa(status));
	}
	else if (str[0] == '$' && str[1] != '?')
	{
		ret = expansion(str, 0, env, status);
		free(str);
		return (ret);
	}
	while (str[i] != '$' && str[i])
		i++;
	aux = ft_substr(str, 0, i); // Quedarme con la primera mitad de comillas o lo que sea
	tmp = expansion(str, i, env, status);
	ret = ft_strjoin(aux, tmp);
	free(aux);
	free(tmp);
	return (ret);
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
			|| !ft_strncmp(s1, ">", 1) && !ft_strncmp(s1, "<", 1))
		{
			ft_putendl_fd("syntax error near unexpected token `>>'", 2);
			utils->status = 2;
			return (0);
		}
		else if (!ft_strncmp(s1, "<<", 2) && !ft_strncmp(tmp->str, ">>", 2)
			|| !ft_strncmp(s1, "<", 1) && !ft_strncmp(s1, ">", 1))
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
	// REVISAR CASOS COMO echo $'USER'
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
