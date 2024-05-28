/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:04:54 by nvillalt          #+#    #+#             */
/*   Updated: 2024/05/28 15:56:45 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static char	*expand_env_var(char *str, t_expand *exp_utils, t_token *tmp)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (str[++i])
	{
		if (str[i] == 39 && !flag)
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
	}
	tmp->expand = EXPAND;
	return (var_expanded(str, exp_utils));
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
			|| (!ft_strncmp(s1, "<", 1) && !ft_strncmp(tmp->str, ">", 1))
			|| (!ft_strncmp(s1, "<", 1) && !ft_strncmp(tmp->str, "<", 1))
			|| (!ft_strncmp(s1, "<<", 2) && !ft_strncmp(tmp->str, "|", 1))
			|| (!ft_strncmp(s1, "<", 2) && !ft_strncmp(tmp->str, "|", 1)))
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
	t_token		*tmp;
	t_expand	*exp_utils;
	int			i;

	i = 0;
	tmp = utils->token_list;
	exp_utils = init_exp(utils);
	while (tmp->str)
	{
		if (!check_valid_redir(tmp->str, tmp->next, utils))
		{
			clear_token_list(&utils->token_list);
			return (0);
		}
		if (check_valid_symbol(tmp->str) && check_dollar(tmp->str))
			tmp->str = expand_env_var(tmp->str, exp_utils, tmp);
		if (tmp->str && tmp->next == NULL)
			break ;
		if (tmp->str)
			tmp = tmp->next;
	}
	free(exp_utils);
	return (1);
}
