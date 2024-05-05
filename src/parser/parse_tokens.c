



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
int create_file(t_redir **redir_list, char *document, int type, t_redir **head)
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

int parse_tokens(t_utils *utils)
{
    t_parse *head;
    t_token *tokens;

    init_process(&utils->process);
    tokens = utils->token_list;
    while (tokens->next != NULL)
    {
        if (!ft_strcmp(tokens->str, ">") ||  !ft_strcmp(tokens->str, ">|"))
        {
            create_file(&utils->process->redirec, tokens->next->str, GREAT, &utils->process->redirec_head);
            tokens = tokens->next; // Avanzo al siguiente token porque cuando salga de la condición ya avanzará otro más
        }
        else if (!ft_strcmp(tokens->str, "<"))
        {
            create_file(&utils->process->redirec, tokens->next->str, MINUS, &utils->process->redirec_head);
            tokens = tokens->next;
        }
        else if (!ft_strcmp(tokens->str, ">>"))
        {
            printf("ENtras?\n");
            create_file(&utils->process->redirec, tokens->next->str, APPEND, &utils->process->redirec_head);
            tokens = tokens->next;
        }
        else if (!ft_strcmp(tokens->str, "<<"))
        {
            create_file(&utils->process->redirec, tokens->next->str, HEREDOC, &utils->process->redirec_head);
            tokens = tokens->next;
        }
        else
            tokens = tokens->next;
    }
    t_redir *print;

    print = utils->process->redirec_head;
    while (print->next != NULL)
    {
        printf("Imprimelo:\n");
        printf("redir type: %d\nredir doc: %s\nredir heredoc: %s\nheredoc flag: %d\n------\n", print->redir_type, print->doc, print->heredoc_file, print->heredoc_flag);
        print = print->next;
        // << "hola" << hola <infile < "inf"ile >> append >out
    }
    clear_token_list(&utils->token_list); // Ya no se va a necesitar más el token list
    return (0);
}