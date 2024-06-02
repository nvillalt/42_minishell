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

void	free_parse_list(t_parse	*process)
{
	t_parse	*temp;
	t_redir	*redir_temp;

	while(process)
	{
		if(process->cmd)
			free_matrix(process->cmd); //No se libera bien hasta hacer una reserva correcta
		process->redirec = process->redirec_head;
		while(process->redirec)
		{
			redir_temp = process->redirec;
			if (process->redirec->doc)
				free(process->redirec->doc);
			if (process->redirec->heredoc_file)
				free(process->redirec->heredoc_file);
			process->redirec = process->redirec->next;
			free(redir_temp);
		}
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
	if (utils->process)
		free_lists(utils);
	if (utils->pid_array)
		free(utils->pid_array);
}

void	free_lists(t_utils	*utils)
{
	if (utils->process)
	{
		free_parse_list(utils->process);
		utils->process = NULL;
	}
	if (utils->pid_array)
	{
		free(utils->pid_array);
		utils->pid_array = NULL;
	}
}
