



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
    printf("CONSIGO ENTRAR AQUI \n");
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

    if(!init_process(&new) && process_list != NULL) // *process_list o solo process_list -> Revisar tmb para redir_list
    {
        free_process(process_list);
        return (0);
    }
    counter = 0;
    move = *tokens;
    while (move->next != NULL)
    {
        counter++;
        if (!ft_strcmp(move->next->str, "|"))
            break ;
        move = move->next;
    }
    move = *tokens;
    i = 0;
    while (i < counter)
    {
        printf("que numero: %d\n", i);
        new->cmd = ft_calloc(sizeof(char *), counter + 1);
        if (!new->cmd)
            return (0);
        new->cmd[i] = clean_quotes(move->str);
        printf("Comando de CMD ----> %s\n", new->cmd[i]);
        move = move->next;
        i++;
    }
    printf("Cmds en new: %s\n", new->cmd[0]);
    printf("AL FINAL: %s\n", move->str);
    *tokens = move;
    if (!add_process(process_list, new))
    {
        free_process(process_list);
        return (0);
    }
    return (1);
}


// int parse_tokens(t_utils *utils)
// {
//     t_parse *head;
//     t_token *tokens;

//     init_process(&utils->process);
//     tokens = utils->token_list;
//     while (tokens->next != NULL)
//     {
//         if (!ft_strcmp(tokens->str, ">") || !ft_strcmp(tokens->str, ">|"))
//             create_redir(&utils->process->redirec, tokens->next->str, GREAT, &utils->process->redirec_head);
//         else if (!ft_strcmp(tokens->str, "<"))
//             create_redir(&utils->process->redirec, tokens->next->str, MINUS, &utils->process->redirec_head);
//         else if (!ft_strcmp(tokens->str, ">>"))
//             create_redir(&utils->process->redirec, tokens->next->str, APPEND, &utils->process->redirec_head);
//         else if (!ft_strcmp(tokens->str, "<<"))
//             create_redir(&utils->process->redirec, tokens->next->str, HEREDOC, &utils->process->redirec_head);
//         // else
//         //     create_process(&utils->process, &tokens);
//         // printf("Process tras create_process: %s\n", utils->process->next->cmd[0]);
//         // printf("Tokens: %s \n", tokens->str);
//         tokens = tokens->next;
//         // printf("Tokens: %s \n", tokens->str);
//     }
//     t_redir *print;

//     print = utils->process->redirec_head;
//     if (print != NULL)
//     {
//         printf("IMPRIMO REDIR:\nDoc: %s\nHeredoc: %s\nRedir Type: %d\nHeredoc Flag: %d\n- - - - - - -\n", print->doc, print->heredoc_file, print->redir_type, print->heredoc_flag);
//         while(print->next != NULL)
//         {
//             print = print->next;
//             printf("IMPRIMO REDIR:\nDoc: %s\nHeredoc: %s\nRedir Type: %d\nHeredoc Flag: %d\n- - - - - -\n", print->doc, print->heredoc_file, print->redir_type, print->heredoc_flag);
//         }
//     }
//     // t_parse *print_proc;

//     // print_proc = utils->process;
//     // if (print_proc != NULL)
//     // {
//     //     printf("IMPRIMO PROCESO:\nCmd: %s\nBuilt-in: %d\n", print_proc->cmd[0],print_proc->built_in);
//     //     while (print_proc->next != NULL)
//     //     {
//     //         print_proc = print_proc->next;
//     //         printf("IMPRIMO PROCESO:\nCmd: %s\nBuilt-in: %d\n", print_proc->cmd[0],print_proc->built_in);
//     //     }
//     // }
//     clear_token_list(&utils->token_list); // Ya no se va a necesitar más el token list
//     return (0);
// }
