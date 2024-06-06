/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_builder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:04:54 by nvillalt          #+#    #+#             */
/*   Updated: 2024/06/06 17:00:03 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	handle_printing_dollar(t_exp *exp_utils, int i, char **s, int flag)
{
	if (flag == 1)
	{
		*s = ft_itoa(exp_utils->status);
		return (i += 2);
	}
	else if (flag == 2)
	{
		*s = ft_strdup("$");
		return (i += 1);
	}
	else if (flag == 3)
	{
		*s = ft_strdup("$");
		return (i += 2);
	}
	return (1);
}

int	expand_dbl_quote(char *s, t_exp *exp_utils, char **ret, int i)
{
	char	*aux;
	char	*tmp;
	int		j;

	aux = NULL;
	tmp = NULL;
	j = i;
	i++;
	while (s[i] != 34)
		i++;
	i++;
	aux = ft_substr(s, j, i - j);
	tmp = var_expanded(aux, exp_utils);
	aux = ft_strjoin_expand(*ret, tmp);
	*ret = aux;
	if (tmp)
		free(tmp);
	return (i);
}

int	handle_sgl_quote(char *s, char **ret, int i)
{
	char	*aux;
	char	*tmp;
	int		j;

	aux = NULL;
	tmp = NULL;
	j = i;
	i++;
	while (s[i] != 39)
		i++;
	i++;
	aux = ft_substr(s, j, i - j);
	tmp = ft_strjoin_expand(*ret, aux);
	if (aux)
		free(aux);
	*ret = tmp;
	return (i);
}

int	expand_dollar(char *s, t_exp *exp_utils, char **ret, int i)
{
	char	*aux;
	char	*tmp;
	int		j;

	aux = NULL;
	tmp = NULL;
	j = i;
	i++;
	while (ft_isalnum(s[i]))
		i++;
	if (s[i] == '?')
		i++;
	aux = ft_substr(s, j, i - j);
	tmp = var_expanded(aux, exp_utils);
	aux = ft_strjoin_expand(*ret, tmp);
	*ret = aux;
	if (tmp)
		free(tmp);
	return (i);
}

int	not_exp(char *s, char **ret, int i)
{
	char	*aux;
	char	*tmp;
	int		j;

	aux = NULL;
	tmp = NULL;
	j = i;
	if (s[i])
	{
		while (s[i] != 34 && s[i] != 39 && s[i] != '$' && s[i] != '\0')
		{
			i++;
		}
		aux = ft_substr(s, j, i - j);
		tmp = ft_strjoin_expand(*ret, aux);
		if (aux)
			free(aux);
		*ret = tmp;
	}
	return (i);
}
