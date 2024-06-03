/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:19:10 by nvillalt          #+#    #+#             */
/*   Updated: 2024/06/03 21:11:11 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	assign_builtins(t_utils *utils)
{
	t_parse	*p;

	p = utils->process;
	while (p && p->cmd && p->cmd[0])
	{
		if (!ft_strncmp(p->cmd[0], "echo", 4) && ft_strlen(p->cmd[0]) == 4)
			p->built_in = ECHO;
		else if (!ft_strncmp(p->cmd[0], "pwd", 3) && ft_strlen(p->cmd[0]) == 3)
			p->built_in = PWD;
		else if (!ft_strncmp(p->cmd[0], "env", 3) && ft_strlen(p->cmd[0]) == 3)
			p->built_in = ENV;
		else if (!ft_strncmp(p->cmd[0], "unset", 5)
			&& ft_strlen(p->cmd[0]) == 5)
			p->built_in = UNSET;
		else if (!ft_strncmp(p->cmd[0], "cd", 2) && ft_strlen(p->cmd[0]) == 2)
			p->built_in = CD;
		else if (!ft_strcmp(p->cmd[0], "exit") && ft_strlen(p->cmd[0]) == 4)
			p->built_in = EXIT;
		else if (!ft_strncmp(p->cmd[0], "export", 6)
			&& ft_strlen(p->cmd[0]) == 6)
			p->built_in = EXPORT;
		else
			p->built_in = 0;
		p = p->next;
	}
}

static void	divide_commands(t_parse **node, int i)
{
	char	**aux;
	char	**ret;
	int		j;
	int		k;

	j = 0;
	k = 0;
	aux = ft_split((*node)->cmd[i], ' ');
	ret = ft_calloc(sizeof(char *), count(aux) + count((*node)->cmd) + 1);
	if (!ret)
		return ;
	if (i != 0)
	{
		while (j < i)
		{
			ret[j] = ft_strdup((*node)->cmd[j]);
			j++;
		}
	}
	dup_matrix(ret, aux, j, k);
	free_matrix((*node)->cmd);
	free_matrix(aux);
	(*node)->cmd = ret;
}

static int	assign_process(t_parse **node, char *str, int expand)
{
	char	**temp;
	int		i;
	int		j;

	i = 0;
	j = -1;
	if ((*node)->cmd == NULL)
		init_process_cmd(node);
	else
	{
		while ((*node)->cmd[i])
			i++;
		temp = ft_calloc(sizeof(char *), i + 2);
		if (!temp)
			return (0);
		while (++j <= i)
			temp[j] = (*node)->cmd[j];
		free((*node)->cmd);
		(*node)->cmd = temp;
	}
	(*node)->cmd[i] = clean_quotes(str);
	if (expand == EXPAND && ((*node)->cmd[i][0] != 39
		|| (*node)->cmd[i][0] != 34))
		divide_commands(node, i);
	return (1);
}

static int	create_process(t_parse **process_list, t_token **move)
{
	t_parse	*node;
	t_token	*i;

	node = NULL;
	if (!init_process(&node) && process_list != NULL)
		return (perror("minishell"), 0);
	i = *move;
	while (i)
	{ // Pasar a una función
		if (!ft_strcmp(i->str, "<") || !ft_strcmp(i->str, "<<")
			|| !ft_strcmp(i->str, ">|") || !ft_strcmp(i->str, "|>")
			|| !ft_strcmp(i->str, ">") || !ft_strcmp(i->str, ">>"))
		{
			if (!handle_redirection(&i, &node->redirec, &node->redirec_head))
				return (FUNC_FAILURE);
		}
		else if (!ft_strcmp(i->str, "|"))
			break ;
		else if (!assign_process(&node, i->str, i->expand))
			return (FUNC_FAILURE);
		if (i->next == NULL)
			break ;
		i = i->next;
	}
	if (!add_process(process_list, node))
		return (0);
	*move = i;
	return (1);
}

int	parse_tokens(t_utils *utils)
{
	t_token	*move;

	move = utils->token_list;
	while (move->str)
	{
		create_process(&utils->process, &move);
		if (move->str && move->next == NULL)
			break ;
		if (move->str)
			move = move->next;
	}
	assign_builtins(utils);
	clear_token_list(&utils->token_list);
	return (0);
}
