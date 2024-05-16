#include "../../minishell.h"

static int	check_valid_symbol(char *str) // Implementar en parse, un if else con handle_quotes o esto, dependiendo
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

static char	*expand_env_var(char *str, char **env)
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
	//return ("pinga\n");
	return (var_expanded(str, env));
}

int	expansor(t_utils *utils) // Utils para acceder al env y 
{
	t_token	*tmp;

	tmp = utils->token_list;
	while (tmp->str)
	{
		if (check_valid_symbol(tmp->str))
		{
			tmp->str = expand_env_var(tmp->str, utils->env);
			printf("Var expandida: %s\n", tmp->str);
		}
		if (tmp->str && tmp->next == NULL)
			break ;
		if (tmp->str)
			tmp = tmp->next;
	}
	return (1);
}