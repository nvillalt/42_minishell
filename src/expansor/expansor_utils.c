/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:04:54 by nvillalt          #+#    #+#             */
/*   Updated: 2024/06/06 15:54:05 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_expand	*init_exp(t_utils *utils)
{
	t_expand	*exp_utils;

	exp_utils = ft_calloc(sizeof(t_expand), 1);
	if (!exp_utils)
		return (NULL);
	exp_utils->str = utils->token_list->str;
	exp_utils->status = utils->status;
	exp_utils->env = utils->env;
	return (exp_utils);
}

char	*ft_strjoin_expand(char *s1, char *s2)
{
	char	*ptr;
	size_t	i;
	size_t	k;

	if (!s1 || !s2)
		s1 = ft_strdup("");
	i = -1;
	k = 0;
	ptr = (char *)ft_calloc((ft_strlen_gnl(s1)
				+ ft_strlen_gnl(s2) + 1), sizeof(char));
	if (!ptr)
		return (NULL);
	while (s1[++i])
		ptr[i] = s1[i];
	while (s2[k])
	{
		ptr[i] = s2[k];
		i++;
		k++;
	}
	if (s1 != NULL)
		free(s1);
	return (ptr);
}

int	check_dollar(char *str)
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

int	check_valid_redir(char *s1, t_token *tmp, t_utils *utils)
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

int	free_expansor(t_token **token_list, t_expand *exp_utils)
{
	if (token_list)
		clear_token_list(token_list, TOKEN_ERR);
	if (exp_utils)
		free(exp_utils);
	perror("minishell");
	return (0);
}
