#include "../../minishell.h"

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while(matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	return ;
}

void	free_redir_list(t_parse *process) //Libera todos los redir de todos los nodos de parse
{
	t_redir	*temp;

	while(process)
	{
		while(process->redirec)
		{
			if (process->redirec->doc)
				free(process->redirec->doc);
			if (process->redirec->heredoc_file)
				free(process->redirec->heredoc_file);
			temp = process->redirec;
			process->redirec = process->redirec->next;
			free(temp);
		}
		process = process->next;
	}
}

void	free_parse_list(t_parse	*process)
{
	t_parse	*temp;

	while(process)
	{
		if(process->cmd)
			free_matrix(process->cmd); //No se libera bien hasta hacer una reserva correcta
		temp = process;
		process = process->next;
		free(temp);
	}
}

void	free_utils(t_utils *utils)
{
	if (utils->env)
		free_matrix(utils->env);
	if (utils->path)
		free_matrix(utils->path);
	if (utils->process->redirec)
		free_redir_list(utils->process);
	if (utils->process)
		free_parse_list(utils->process);
	if (utils->pid_array)
		free(utils->pid_array);
}

void	free_lists(t_utils	*utils)
{
	utils->process->redirec = utils->process->redirec_head;
	if (utils->process->redirec)
		free_redir_list(utils->process);
	if (utils->process)
		free_parse_list(utils->process);
	if (utils->pid_array)
		free(utils->pid_array);
}
