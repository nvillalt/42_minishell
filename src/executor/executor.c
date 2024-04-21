#include "../../minishell.h"

static void	create_out(t_redir **redirec, char *token)
{
	t_redir	*node;
	t_redir	*head;

	node = malloc(sizeof(t_redir));
	node->next = NULL;
	node->doc = token;
	node->redir_type = GREAT;
	if (*redirec == NULL)
		*redirec = node;
	else
	{
		head = *redirec;
		while((*redirec)->next != NULL)
			*redirec = (*redirec)->next;
		(*redirec)->next = node;
		*redirec = head;
	}
}

static void	create_in(t_redir **redirec, char *token)
{
	t_redir	*node;
	t_redir	*head;

	node = malloc(sizeof(t_redir));
	node->next = NULL;
	node->doc = token;
	node->redir_type = MINUS;
	if (*redirec == NULL)
		*redirec = node;
	else
	{
		head = *redirec;
		while((*redirec)->next != NULL)
			*redirec = (*redirec)->next;
		(*redirec)->next = node;
		*redirec = head;
	}
}

static void	create_out_append(t_redir **redirec, char *token)
{
	t_redir	*node;
	t_redir	*head;

	node = malloc(sizeof(t_redir));
	node->next = NULL;
	node->doc = token;
	node->redir_type = APPEND;
	if (*redirec == NULL)
		*redirec = node;
	else
	{
		head = *redirec;
		while((*redirec)->next != NULL)
			*redirec = (*redirec)->next;
		(*redirec)->next = node;
		*redirec = head;
	}
}

static void	create_heredoc(t_redir **redirec, char *token)
{
	t_redir	*node;
	t_redir	*head;

	node = malloc(sizeof(t_redir));
	node->next = NULL;
	node->doc = token;
	node->redir_type = HEREDOC;
	if (*redirec == NULL)
		*redirec = node;
	else
	{
		head = *redirec;
		while((*redirec)->next != NULL)
			*redirec = (*redirec)->next;
		(*redirec)->next = node;
		*redirec = head;
	}
}

void	create_new_parse_node(t_parse **process)
{
	t_parse	*node;
	t_parse	*head;

	node = malloc(sizeof(t_parse));
	node->cmd = ft_calloc(20, sizeof(char *));
	node->built_in = 0;
	node->redirec = NULL;
	node->next = NULL;
	head = *process;
	while((*process)->next != NULL)
		*process = (*process)->next;
	(*process)->next = node;
	*process = (*process)->next;
	*process = head;
}

static void print_cmds_and_docs(t_utils *utils)
{
	int i = 0;
	while (utils->process->redirec)
	{
		printf("REDIREC DOC: %s\n", utils->process->redirec->doc);
		utils->process->redirec = utils->process->redirec->next;
		i++;
	}
	i = 0;
	while (utils->process->cmd[i])
	{
		printf("PROCESS CMD: %s\n",utils->process->cmd[i]);
		i++;
	}
}

void	dirty_parse(char *input, t_utils *utils)
{
	char	**tokens;
	int		i;
	int		j;

	i = 0;
	j = 0;
	utils->process = ft_calloc(1, sizeof(t_parse));
	utils->process->cmd = ft_calloc(20, sizeof(char *));
	utils->process->built_in = 0;
	utils->process->redirec = NULL;
	utils->process->next = NULL;
	tokens = ft_split(input, ' ');
	while(tokens[i])
	{
		if (ft_strcmp(tokens[i], ">") == 0)
		{
			create_out(&utils->process->redirec, tokens[i + 1]);
			i=i + 2;
		}
		else if (ft_strcmp(tokens[i], "<") == 0)
		{
			create_in(&utils->process->redirec, tokens[i + 1]);
			i=i + 2;
		}
		else if (ft_strcmp(tokens[i], ">>") == 0)
		{
			create_out_append(&utils->process->redirec, tokens[i + 1]);
			i=i + 2;
		}
		else if (ft_strcmp(tokens[i], "<<") == 0)
		{
			create_heredoc(&utils->process->redirec, tokens[i + 1]);
			i=i + 2;
		}
		else if (ft_strcmp(tokens[i], "|") == 0)
		{
	 		print_cmds_and_docs(utils);
			create_new_parse_node(&utils->process);
			utils->process = utils->process->next;
			j = 0;
			i++;
		}
		else
		{
			utils->process->cmd[j] = ft_strdup(tokens[i]);
			i++;
			j++;
		}
	}
	 print_cmds_and_docs(utils);
}