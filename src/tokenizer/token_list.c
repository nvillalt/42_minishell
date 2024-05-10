/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:03:58 by nvillalt          #+#    #+#             */
/*   Updated: 2024/05/09 20:11:20 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	free_tokens(t_token **token_list, char *temp, int n)
{
	if (n == 1)
	{
		clear_token_list(token_list);
		free(temp);
		return (2);
	}
	return (0);
}

int	clear_token_list(t_token **token_list)
{
	t_token	*aux;
	t_token	*next;

	aux = *token_list;
	while (aux)
	{
		next = aux->next;
		if (aux->str)
			free(aux->str);
		free(aux);
		aux = next;
	}
	free(aux);
	*token_list = NULL;
	return (1);
}

int	new_token(t_token **new)
{
	*new = ft_calloc(sizeof(t_token), 1);
	if (!(*new))
		return (0);
	(*new)->str = NULL;
	(*new)->next = NULL;
	return (1);
}

int	add_token(t_token **token_list, t_token *new)
{
	t_token	*tmp;

	if (!token_list || !new)
		return (0);
	if (*token_list == NULL)
	{
		*token_list = new;
		return (1);
	}
	tmp = *token_list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}
