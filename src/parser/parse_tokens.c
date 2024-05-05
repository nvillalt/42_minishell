



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
    (*node)->heredoc_flag = 0;
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
	while (process->next)
		process = process->next;
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
        if (document[0] == 34 || document[0] == 39)
            new->heredoc_flag = 1;
        new->heredoc_file = clean_quotes(document);
    }
    if (!add_redir(redir_list, new))
    {
        free_redir(redir_list);
        return (0);
    }
    (*head) = *redir_list;
    return (1);
}

int create_process(t_parse **process_list, t_token **tokens)
{
    t_parse    *new;
    t_token    *move;
    int         counter;
    int         i;

    init_process(&new);
    counter = 0;
    i = 0;
    move = *tokens;
    while (move->next != NULL)
    {
        counter++;
        if (!ft_strcmp(move->next->str, "|"))
            break ;
        move = move->next;
    }
    printf("Counter: %d\n", counter);
    move = *tokens;
    printf("EN TOKENS: %s\n\n", move->str);
    while (i < counter)
    {
        printf("Entras?\n");
        new->cmd = ft_calloc(sizeof(char *), counter + 1);
        if (!new->cmd)
            return (0);
        new->cmd[i] = clean_quotes(move->str);
        i++;
    }
    i = 0;
    while (new->cmd[i])
    {
        printf("Comand: %s\n", new->cmd[i]);
        i++;
    }
}

int parse_tokens(t_utils *utils)
{
    t_parse *head;
    t_token *tokens;

    init_process(&utils->process);
    tokens = utils->token_list;
    while (tokens->next != NULL)
    {
        if (!ft_strcmp(tokens->str, ">") ||  !ft_strcmp(tokens->str, ">|"))
            create_redir(&utils->process->redirec, tokens->next->str, GREAT, &utils->process->redirec_head);
        else if (!ft_strcmp(tokens->str, "<"))
            create_redir(&utils->process->redirec, tokens->next->str, MINUS, &utils->process->redirec_head);
        else if (!ft_strcmp(tokens->str, ">>"))
            create_redir(&utils->process->redirec, tokens->next->str, APPEND, &utils->process->redirec_head);
        else if (!ft_strcmp(tokens->str, "<<"))
            create_redir(&utils->process->redirec, tokens->next->str, HEREDOC, &utils->process->redirec_head);
        else
            create_process(&utils->process, &tokens);
        tokens = tokens->next;
    }
    t_redir *print;

    print = utils->process->redirec_head;
    printf("IMPRIMO REDIR:\nDoc: %s\nHeredoc: %s\nRedir Type: %d\nHeredoc Flag: %d\n- - - - - - -\n", print->doc, print->heredoc_file, print->redir_type, print->heredoc_flag);
    while(print->next != NULL)
    {
        print = print->next;
        printf("IMPRIMO REDIR:\nDoc: %s\nHeredoc: %s\nRedir Type: %d\nHeredoc Flag: %d\n- - - - - -\n", print->doc, print->heredoc_file, print->redir_type, print->heredoc_flag);
    }
    clear_token_list(&utils->token_list); // Ya no se va a necesitar más el token list
    return (0);
}
