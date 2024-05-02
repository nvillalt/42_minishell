



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
}

int init_redir(t_redir **node)
{
    *node = ft_calloc(sizeof(t_redir), 1);
    if (!node)
        return (0);
    (*node)->heredoc_file = NULL;
    (*node)->heredoc_flag = 0;
    (*node)->doc = NULL;
    (*node)->redir_type = GREAT;
    (*node)->fd = -1;
}

int create_outfile(t_redir **redir, char *document)
{
    t_redir *new;
    t_redir *head;

    init_redir(&new);
    new->doc = clean_quotes(document);
    if (*redir == NULL)
        *redir = new;
    else
    {
        head = *redir;
        while ((*redir)->next != NULL)
            *redir = (*redir)->next;
        (*redir)->next = new;
        *redir = head;
    }
}



int parse_tokens(t_utils *utils)
{
    t_parse *head;
    t_token *tokens;

    init_process(&head);
    tokens = utils->token_list;
    while (tokens->next != NULL)
    {
        if (!ft_strcmp(tokens->str, ">"))
        {
            create_outfile(&utils->process->redirec, tokens->next->str);
        }
    }
    clear_token_list(&utils->token_list); // Ya no se va a necesitar más el token list
    return (0);
}