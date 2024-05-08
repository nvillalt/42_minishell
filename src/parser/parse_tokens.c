



#include  "../../minishell.h"

int init_process(t_parse **process)
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

int init_redir(t_redir **node, int type)
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
static void	assign_builtins(t_utils *utils) //BORRAR EVENTUALMENTE
{
	t_parse *process;

	process = utils->process;
	while (process->next != NULL)
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

int add_redir(t_redir **redir_list, t_redir *new)
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
int add_process(t_parse **process_list, t_parse *new)
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
int free_redir(t_redir **redir_list)
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

int free_process(t_parse **process_list)
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
int create_redir(t_redir **redir_list, char *document, int type, t_redir **head)
{
	t_redir *new;

	if (!init_redir(&new, type) && redir_list != NULL)
	{
		free_redir(redir_list);
		return (0);
	}
	if (type == GREAT || type == MINUS || type == APPEND)
		new->doc = clean_quotes(document);
	else if (type == HEREDOC)
	{
		if (assert_quotes(document))
			new->heredoc_flag = NOT_EXPAND;
		new->heredoc_file = clean_quotes(document);
	}
	if (!add_redir(redir_list, new))
	{
		free_redir(redir_list); // cambiar esta liberación
		return (0);
	}
	(*head) = *redir_list;
	return (1);
}

// RESERVAS PARA UTILS MEJOR LIBERAR CUANDO SALGA DEL TODO

int	handle_redirections(t_token **iterate, t_redir **redir_list, t_redir **redir_head)
{
	if (!ft_strcmp((*iterate)->str, ">") || !ft_strcmp((*iterate)->str, ">|"))
	{
		create_redir(redir_list, (*iterate)->next->str, GREAT, redir_head);
		*iterate = (*iterate)->next;
	}
	else if (!ft_strcmp((*iterate)->str, "<"))
	{
		create_redir(redir_list, (*iterate)->next->str, MINUS, redir_head);
		*iterate = (*iterate)->next;
	}
	else if (!ft_strcmp((*iterate)->str, ">>"))
	{
		create_redir(redir_list, (*iterate)->next->str, APPEND, redir_head);
		*iterate = (*iterate)->next;
	}
	else if (!ft_strcmp((*iterate)->str, "<<"))
	{
		create_redir(redir_list, (*iterate)->next->str, HEREDOC, redir_head);
		*iterate = (*iterate)->next;
	}
	return (1);
}

int	assign_process(t_parse **node, char *str)
{
	char	**temp;
	int		i;
	int		j;

	i = 0;
	j = -1;
	if ((*node)->cmd == NULL)
	{
		(*node)->cmd = ft_calloc(sizeof(char *), 2); // For null termination
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
		while (++j < i)
			temp[j] = (*node)->cmd[j];
		free((*node)->cmd);
		(*node)->cmd = temp;
	}
	(*node)->cmd[i] = clean_quotes(str);
	if (!(*node)->cmd[i])
		return (0);
	return (1);
}

int	create_process(t_parse **process_list, t_token **token_list, t_token **move)
{
	t_parse	*node;
	t_token	*i;

	node = NULL;
	if (!init_process(&node) && process_list != NULL) // REVISAR LIBERACIONES
		return (0);
	i = *move;
	while (i->next != NULL)
	{
		if (!ft_strcmp(i->str, "<") || !ft_strcmp(i->str, "<<") || !ft_strcmp(i->str, ">|")
			|| !ft_strcmp(i->str, ">") || !ft_strcmp(i->str, ">>"))
			handle_redirections(&i, &node->redirec, &node->redirec_head);
		else if (!ft_strcmp(i->str, "|"))
			break ;
		else
			assign_process(&node, i->str);
		i = i->next;
	}
	if (!add_process(process_list, node))
		return (0);
	int	j = 0;
	while (node->cmd[j])
	{
		printf("DENTRO DE CMD: %s\n", node->cmd[j]);
		j++;
	}
	// Test: ls -la < infile >>append | wc -l "    hola"
	*move = i->next;
	return (1);
}

int parse_tokens(t_utils *utils)
{
	t_token *move;

	move = utils->token_list;
	// Gestionar aparte
	// if (move->next == NULL)
	// 	single_token(utils);
	while (move->next != NULL)
	{
		create_process(&utils->process, &utils->token_list, &move);
	}
	printf("Terminado");
	assign_builtins(utils);
	clear_token_list(&utils->token_list);
	return (0);
}