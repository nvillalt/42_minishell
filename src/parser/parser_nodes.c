/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:09:30 by nvillalt          #+#    #+#             */
/*   Updated: 2024/05/30 13:56:08 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	init_process(t_parse **process)
{
	*process = ft_calloc(sizeof(t_parse), 1);
	if (!(*process))
		return (0);
	(*process)->cmd = NULL;
	(*process)->built_in = 0;
	(*process)->redirec = NULL;
	(*process)->redirec_head = NULL;
	(*process)->next = NULL;
	return (1);
}

int	init_redir(t_redir **node, int type)
{
	*node = ft_calloc(sizeof(t_redir), 1);
	if (!node)
		return (0);
	(*node)->heredoc_file = NULL;
	(*node)->heredoc_flag = EXPAND;
	(*node)->doc = NULL;
	(*node)->redir_type = type;
	(*node)->fd = -1;
	(*node)->next = NULL;
	return (1);
}

int	add_redir(t_redir **redir_list, t_redir *new)
{
	t_redir *head;

	if (!redir_list || !new)
		return (0);
	if (*redir_list == NULL)
	{
		*redir_list = new;
		return (1);
	}
	else
	{
		head = *redir_list;
		while ((*redir_list)->next != NULL)
			*redir_list = (*redir_list)->next;
		(*redir_list)->next = new;
		*redir_list = head;
	}
	return (1);
}

int	add_process(t_parse **process_list, t_parse *new)
{
	t_parse *head;

	if (!process_list || !new)
		return (0);
	if (*process_list == NULL)
	{
		*process_list = new;
		return (1);
	}
	else
	{
		head = *process_list;
		while ((*process_list)->next != NULL)
			*process_list = (*process_list)->next;
		(*process_list)->next = new;
		*process_list = head;
	}
	return (1);
}

static int	free_redir(t_redir **redir_list)
{
	t_redir *aux;
	t_redir *next;

	aux = *redir_list;
	while (aux->next != NULL)
	{
		next = aux->next;
		if (aux->doc)
			free(aux->doc);
		else if (aux->heredoc_file)
			free(aux->heredoc_file);
		free(aux);
		aux = next;
	}
	free(aux);
	*redir_list = NULL;
	return (1);
}

int	free_process(t_parse **process_list)
{
	t_parse *aux;
	t_parse *next;

	aux = *process_list;
	while (aux->next != NULL)
	{
		next = aux->next;
		if (aux->cmd)
			free_matrix(aux->cmd);
		if (aux->redirec_head)
			free_redir(&aux->redirec_head);
		free(aux);
		aux = next;
	}
	free(aux);
	*process_list = NULL;
	return (1);   
}
