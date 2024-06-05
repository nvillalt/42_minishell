/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:14:09 by nvillalt          #+#    #+#             */
/*   Updated: 2024/06/05 17:54:15 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	count_symbols(char *input, int i, t_utils *utils)
{
	int	count;

	count = 0;
	while (input[i] == '<' || input[i] == '>')
	{
		i++;
		count++;
	}
	if (count > 2)
	{
		utils->status = 2;
		ft_putstr_fd("minishell:", 2);
		ft_putendl_fd("syntax error near unexpected token `>>'", 2);
		return (0);
	}
	return (1);
}

int	syntax_error(char *input, t_utils *utils)
{
	int	flag;
	int	i;

	flag = 0;
	i = 0;
	while (input[i])
	{
		if ((input[i] == 34 || input [i] == 39) && flag == 0)
		{
			flag = input[i];
			i++;
			while (input[i] != flag)
				i++;
			flag = 0;
		}
		if ((input[i] == '<' || input[i] == '>') && !flag)
		{
			if (!count_symbols(input, i, utils))
				return (0);
		}
		i++;
	}
	return (1);
}

int	check_redirections(char *input)
{
	if (input[0] == '>' && input[1] == '>' && input[2] == '>')
		return (2);
	if (input[0] == '>' && input[1] == '>' && input[2] == '|')
		return (3);
	if (input[0] == '<' && input[1] == '<' && input[2] == '<')
		return (4);
	if (input[0] == '|' && input[1] == '<')
		return (5);
	if (input[0] == '<' && input[1] == '|')
		return (6);
	if (input[0] == '|' && input[1] == '|')
		return (7);
	if (input[0] == '>' && input[1] == '<')
		return (8);
	if (input[0] == '<' && input[1] == '>')
		return (9);
	return (1);
}

static int	create_redir(t_redir **redir, char *doc, int type, t_redir **head)
{
	t_redir	*new;

	if (!init_redir(&new, type) && redir != NULL)
		return (0);
	if (type == GREAT || type == MINUS || type == APPEND)
		new->doc = clean_quotes(doc);
	else if (type == HEREDOC)
	{
		if (assert_quotes(doc))
			new->heredoc_flag = EXPAND;
		new->doc = clean_quotes(doc);
	}
	if (!add_redir(redir, new))
		return (0);
	(*head) = *redir;
	return (1);
}

int	handle_redirection(t_token **i, t_redir **redir_list, t_redir **redir_head)
{
	if ((*i)->next != NULL)
	{
		if (!ft_strncmp((*i)->str, ">>", 2))
		{
			create_redir(redir_list, (*i)->next->str, APPEND, redir_head);
			*i = (*i)->next;
		}
		else if (!ft_strncmp((*i)->str, ">", 1) || !ft_strcmp((*i)->str, ">|"))
		{
			create_redir(redir_list, (*i)->next->str, GREAT, redir_head);
			*i = (*i)->next;
		}
		else if (!ft_strncmp((*i)->str, "<<", 2))
		{
			create_redir(redir_list, (*i)->next->str, HEREDOC, redir_head);
			*i = (*i)->next;
		}
		else if (!ft_strncmp((*i)->str, "<", 1))
		{
			create_redir(redir_list, (*i)->next->str, MINUS, redir_head);
			*i = (*i)->next;
		}
		return (1);
	}
	return (0);
}
