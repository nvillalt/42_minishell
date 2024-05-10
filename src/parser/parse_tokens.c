/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:19:10 by nvillalt          #+#    #+#             */
/*   Updated: 2024/05/09 20:26:40 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../minishell.h"

static void	assign_builtins(t_utils *utils)
{
	t_parse *process;

	process = utils->process;
	while (process && process->cmd)
	{
		if (ft_strncmp(process->cmd[0], "echo", 4) == 0 && ft_strlen(process->cmd[0]) == 4)
			process->built_in = ECHO;
		else if (ft_strncmp(process->cmd[0], "pwd", 3) == 0 && ft_strlen(process->cmd[0]) == 3)
			process->built_in = PWD;
		else if (ft_strncmp(process->cmd[0], "env", 3) == 0 && ft_strlen(process->cmd[0]) == 3)
			process->built_in = ENV;
		else if (ft_strncmp(process->cmd[0], "unset", 5) == 0 && ft_strlen(process->cmd[0]) == 5)
			process->built_in = UNSET;
		else if (ft_strncmp(process->cmd[0], "cd", 2) == 0 && ft_strlen(process->cmd[0]) == 2)
			process->built_in = CD;
		else if (ft_strncmp(process->cmd[0], "exit", 4) == 0 && ft_strlen(process->cmd[0]) == 4)
			process->built_in = EXIT;
		else if (ft_strncmp(process->cmd[0], "export", 6) == 0 && ft_strlen(process->cmd[0]) == 6)
			process->built_in = EXPORT;
		else
			process->built_in = 0;
		process = process->next;
	}
}

static int	assign_process(t_parse **node, char *str)
{
	char	**temp;
	int		i;
	int		j;

	i = 0;
	j = -1;
	if ((*node)->cmd == NULL)
	{
		(*node)->cmd = ft_calloc(sizeof(char *), 2);
		if (!(*node)->cmd)
			return (0);
	}
	else
	{
		while ((*node)->cmd[i])
			i++;
		temp = ft_calloc(sizeof(char *), i + 1);
		if (!temp)
			return (0);
		while (++j <= i)
			temp[j] = (*node)->cmd[j];
		free((*node)->cmd);
		(*node)->cmd = temp;
	}
	(*node)->cmd[i] = clean_quotes(str);
	if (!(*node)->cmd[i])
		return (0);
	return (1);
}

static int	create_process(t_parse **process_list, t_token **move)
{
	t_parse	*node;
	t_token	*i;

	node = NULL;
	if (!init_process(&node) && process_list != NULL)
		return (0);
	i = *move;
	while (i)
	{
		if (!ft_strcmp(i->str, "<") || !ft_strcmp(i->str, "<<")
			|| !ft_strcmp(i->str, ">|")
			|| !ft_strcmp(i->str, ">") || !ft_strcmp(i->str, ">>"))
			handle_redirection(&i, &node->redirec, &node->redirec_head);
		else if (!ft_strcmp(i->str, "|"))
			break ;
		else if (ft_strcmp(i->str, "|"))
			assign_process(&node, i->str);
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
	while (move->next != NULL)
	{
		create_process(&utils->process, &move);
		if (move->next)
			move = move->next;
	}
	assign_builtins(utils);
	clear_token_list(&utils->token_list);
	return (0);
}
