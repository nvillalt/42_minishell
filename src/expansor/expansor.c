/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:04:54 by nvillalt          #+#    #+#             */
/*   Updated: 2024/06/05 20:10:15 by nvillalt         ###   ########.fr       */
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
				|| str[i] == '\\' || str[i] == '('
				|| str[i] == ')')
				return (0);
			i++;
		}
	}
	return (1);
}

static char	*check_expansion(char *str, t_expand *exp_utils, t_token *tmp)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (str[i])
	{
		if (str[i] == 34)
		{
			i = expand_dbl_quote(str, exp_utils, &ret, i);
			tmp->expand = EXPAND;
			tmp->dbl_quote = YES;
		}
		else if (str[i] == 39)
			i = handle_sgl_quote(str, &ret, i);
		else if (str[i] == '$')
		{
			i = expand_dollar(str, exp_utils, &ret, i);
			tmp->expand = EXPAND;
		}
		else
			i = not_expand(str, &ret, i);
	}
	free(str);
	return (ret);
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
			return (clear_token_list(&utils->token_list, TOKEN_ERR));
		if (check_valid_symbol(tmp->str) && check_dollar(tmp->str))
		{
			tmp->str = check_expansion(tmp->str, exp_utils, tmp);
			if (!tmp->str)
				return (free_expansor(&utils->token_list, exp_utils));
		}
		if (tmp->str && tmp->next == NULL)
			break ;
		if (tmp->str)
			tmp = tmp->next;
	}
	free(exp_utils);
	return (1);
}
