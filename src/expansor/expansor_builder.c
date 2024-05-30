/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_builder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:04:54 by nvillalt          #+#    #+#             */
/*   Updated: 2024/05/30 18:10:37 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_mid(char *str, int i, char **s2, t_expand *exp_utils)
{
	char	*tmp;
	int		j;

	if (str[i] == '$' && str[i + 1] == '?')
	{
		*s2 = ft_itoa(exp_utils->status);
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
	*s2 = expand_env(tmp, exp_utils->env);
	free(tmp);
	return (i);
}

int	get_beginning(char *str, int i, char **s1)
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

int	get_end(char *str, int i, char **s1, t_expand *exp_utils)
{
	int		j;
	char	*aux;
	char	*tmp;

	j = i;
	tmp = NULL;
	if (str[i] == '\0')
		*s1 = ft_strdup("");
	while (str[j] != '\0')
	{
		if (str[j] == '$')
			j = get_mid(str, j, &aux, exp_utils);
		else if (str[j] != '$')
		{
			i = j;
			while (str[j] != '\0' && str[j] != '$')
				j++;
			aux = ft_substr(str, i, j - i);
		}
		if (!tmp)
			tmp = ft_strdup(aux);
		else if (tmp)
			tmp = ft_strjoin_expand(tmp, aux);
		free(aux);
	}
	if (tmp != NULL)
		*s1 = tmp;
	return (i);
}

char	*expand_env(char *var, char **env)
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
				return (ft_strdup(ft_strchr(env[i], '=') + 1));
			break ;
		}
		i++;
	}
	return (ft_strdup(""));
}

char	*var_expanded(char *str, t_expand *exp_utils)
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
	i = get_mid(str, i, &s2, exp_utils);
	ret = ft_strjoin(s1, s2);
	if (s1 != NULL)
		free(s1);
	if (s2)
		free(s2);
	i = get_end(str, i, &s1, exp_utils);
	s2 = ft_strjoin(ret, s1);
	if (ret)
		free(ret);
	if (s1)
		free(s1);
	free(str);
	return (s2);
}
