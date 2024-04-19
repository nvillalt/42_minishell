#include "../../minishell.h"

static void	create_out(t_utils *utils, char *token)
{
	t_redir	*node;

	node = malloc(sizeof(t_redir));
	node->doc = token;
	node->redir_type = GREAT;
	while(utils->process->redirec != NULL)
	{
		utils->process->redirec = utils->process->redirec->next;
		utils->process->redirec->next = node;
	}
	printf("%s\n", node->doc);
}

static void	create_in(t_utils *utils, char *token)
{
	t_redir	*node;

	node = malloc(sizeof(t_redir));
	node->doc = token;
	node->redir_type = MINUS;
	while(utils->process->redirec != NULL)
	{
		utils->process->redirec = utils->process->redirec->next;
		utils->process->redirec->next = node;
	}
	printf("%s\n", node->doc);
}

static void	create_out_append(t_utils *utils, char *token)
{
	t_redir	*node;

	node = malloc(sizeof(t_redir));
	node->doc = token;
	node->redir_type = APPEND;
	while(utils->process->redirec != NULL)
	{
		utils->process->redirec = utils->process->redirec->next;
		utils->process->redirec->next = node;
	}
	printf("%s\n", node->doc);
}
/*
static void	add_cmd(t_utils *utils, char *token, int cmd_argc)
{
	utils->process->cmd[cmd_argc] = ft_strdup(tokens);
}
*/
static void	new_parse_node(t_utils *utils, char *token)
{
	t_parse	*node;

	node = malloc(sizeof(t_parse));
	node->cmd[0] = token;
	node->next = NULL;
}

static void	create_here_doc(t_utils *utils, char *token)
{
	t_redir	*node;

	node = malloc(sizeof(t_redir));
	node->doc = token;
	node->redir_type = HEREDOC;
	while(utils->process->redirec != NULL)
	{
		utils->process->redirec = utils->process->redirec->next;
		utils->process->redirec->next = node;
	}
	printf("%s\n", node->doc);
}

void	dirty_parse(char *input, t_utils *utils)
{
	char	**tokens;
	int		proc_num;
	int		i;
	int		cmd_argc;

	i = 1;
	cmd_argc = 1;
	tokens = ft_split(input, ' ');
	utils->process = malloc(sizeof(t_parse));
	utils->process->cmd = ft_calloc(100, sizeof(char *));
	utils->process->cmd[0] = ft_strdup(tokens[0]);
	utils->process->next = NULL;
	while(tokens[i])
	{
		if (ft_strcmp(tokens[i], ">") == 0)
		{
			create_out(utils, tokens[i + 1]);
			i++;
		}

		else if (ft_strcmp(tokens[i], "<") == 0)
		{
			create_in(utils, tokens[i + 1]);
			i++;
		}
		else if (ft_strcmp(tokens[i], ">>") == 0)
		{
			create_out_append(utils, tokens[i + 1]);
			i++;
		}
		else if (ft_strcmp(tokens[i], "<<") == 0)
		{
			create_here_doc(utils, tokens[i + 1]);
			i++;
		}
		else if (ft_strcmp(tokens[i], "|") == 0)
		{
			new_parse_node(utils, tokens[i + 1]);
			i++;
		}
		else
		{
			utils->process->cmd[cmd_argc] = ft_strdup(token[i]);
			cmd_argc++;
		}
		i++;
	}
}