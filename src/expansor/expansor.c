#include "../../minishell.h"

static int	check_valid_symbol(char *str)
{
	int	i;

	i = 0;
	while (str[i] == 34 || str[i] == 39)
		i++;
	if (str[i] == '$' && str[i + 1] == '?')
		return (1);
	if (str[i] == '$')
	{
		if (ft_isdigit(str[i + 1]))
			return (0);
		while (str[i])
		{
			if (str[i] == '-' || str[i] == '!' || str[i] == '?'
				|| str[i] == '\\' || str[i] == '/' ||str[i] == '('
				|| str[i] == ')')
				return (0);
			i++;
		}
	}
	return (1);
}

static char	*expansion(char *str, int *i, char *path, int st)
{
	if (str[*i] == '$' && str[*i + 1] == '?')
	{
		i += 2;
		return (ft_strdup(ft_itoa(st)));
	}
	return (ft_strdup(str));
}

static char	*expand_with_quote(char *str, int i, char *path, int st)
{
	char	*aux;
	char	*tmp;
	char	*ret;

	if (str[0] != '$')
	{
		aux = ft_substr(str, 0, i);
		tmp = expansion(str, &i, path, st);
		ret = ft_strjoin(aux, tmp);
		free(aux);
		free(tmp);
	}
	// if (str[i] == '$' && str[i + 1] == '?')
	// {
	// 	free(str);
	// 	return (ft_strdup(ft_itoa(st)));
	// }
	if (str)
		free(str);
	return (ret);
}

static int	count_len(char *str)
{
	int	flag;
	int	i;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if ((str[i] == 34 || str[i] == 39) && !flag)
		{
			flag = str[i];
			i++;
			while (str[i] != flag)
				i++;
			flag = 0;
		}
		else if (!flag)
			break ;
		i++;
	}
	return (i);
}

static char	*var_expanded(char *str, char **env, int status)
{
	int		i;
	int		j;
	int		total;

	i = 0;
	j = 0;
	printf("ENtra a var_expanded??\n");
	i = count_len(str);
	total = ft_strlen(str); // Ver como cuento esto
	//printf("Len: %d\n", len);
	// while (str[i] == 34 || str[i] == 39)
	// 	i++;
	if (str[i] == '$' && str[i + 1] == '?')
		return (expand_with_quote(str, i, env[j], status));
	while (env[j])
	{
		if (!ft_strncmp(str + i, env[j], i))
			return (expand_with_quote(str, i, env[j], status));
		j++;
	}
	free(str);
	return (ft_strdup(""));
}

static char	*expand_env_var(char *str, char **env, int status)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		printf("Entras?");
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
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	expansor(t_utils *utils) // Utils para acceder al env y 
{
	t_token	*tmp;

	tmp = utils->token_list;
	// Checar el nodo actual y el nodo de después para ver este caso: << >>
	while (tmp->str)
	{
		if (check_valid_symbol(tmp->str) && check_dollar(tmp->str))
		{
			tmp->str = expand_env_var(tmp->str, utils->env, utils->status);
			printf("Var expandida: %s\n", tmp->str);
		}
		if (tmp->str && tmp->next == NULL)
			break ;
		if (tmp->str)
			tmp = tmp->next;
	}
	return (1);
}