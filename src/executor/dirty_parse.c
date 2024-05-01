#include "../../minishell.h"

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

static void	create_out(t_redir **redirec, char *token)
{
	t_redir	*node;
	t_redir	*head;

	node = malloc(sizeof(t_redir));
	node->heredoc_file = NULL;
	node->next = NULL;
	node->doc = ft_strdup(token);
	node->redir_type = GREAT;
	node->fd = -1;
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
	node->heredoc_file = NULL;
	node->next = NULL;
	node->doc = ft_strdup(token);
	node->redir_type = MINUS;
	node->fd = -1;
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
	node->heredoc_file = NULL;
	node->next = NULL;
	node->doc = ft_strdup(token);
	node->redir_type = APPEND;
	node->fd = -1;
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
	node->heredoc_file = NULL;
	node->doc = ft_strdup(token);
	node->redir_type = HEREDOC;
	node->next = NULL;
	node->fd = -1;
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

	node = malloc(sizeof(t_parse));
	node->cmd = ft_calloc(20, sizeof(char *));
	node->built_in = 0;
	node->redirec = NULL;
	node->redirec_head = NULL;
	node->next = NULL;
	if (!*process)
		*process = node;
	while((*process)->next != NULL)
		*process = (*process)->next;
	(*process)->next = node;
	*process = (*process)->next;
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
	t_parse	*head;
	int		i;
	int		j;

	i = 0;
	j = 0;
	utils->process = malloc(sizeof(t_parse));
	utils->process->cmd = ft_calloc(20, sizeof(char *));
	utils->process->built_in = 0;
	utils->process->redirec = NULL;
	utils->process->next = NULL;
	utils->process->redirec_head = NULL;
	head = utils->process;
	tokens = ft_split(input, ' ');
	while(tokens[i])
	{
		if (ft_strcmp(tokens[i], ">") == 0)
		{
			create_out(&utils->process->redirec, tokens[i + 1]);
			utils->process->redirec_head = utils->process->redirec;
			i=i + 2;
		}
		else if (ft_strcmp(tokens[i], "<") == 0)
		{
			create_in(&utils->process->redirec, tokens[i + 1]);
			utils->process->redirec_head = utils->process->redirec;
			i=i + 2;
		}
		else if (ft_strcmp(tokens[i], ">>") == 0)
		{
			create_out_append(&utils->process->redirec, tokens[i + 1]);
			utils->process->redirec_head = utils->process->redirec;
			i=i + 2;
		}
		else if (ft_strcmp(tokens[i], "<<") == 0)
		{
			create_heredoc(&utils->process->redirec, tokens[i + 1]);
			utils->process->redirec_head = utils->process->redirec;
			i=i + 2;
		}
		else if (ft_strcmp(tokens[i], "|") == 0)
		{
	 //		print_cmds_and_docs(utils);
			create_new_parse_node(&utils->process);
			j = 0;
			i++;
		}
		else
		{
			utils->process->cmd[j] = ft_strdup(tokens[i]);
			assign_builtins(utils);
			i++;
			j++;
		}
	}
	utils->process = head;
	free_matrix(tokens);
	//print_cmds_and_docs(utils);
}
