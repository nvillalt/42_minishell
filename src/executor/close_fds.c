#include "../../minishell.h"

void	close_fds(t_parse *process, t_utils *utils) 
{
	while(process)
	{
		process->redirec = process->redirec_head;
		while(process->redirec)
		{
			if(process->redirec->fd != -1)
			{
				close(process->redirec->fd);
				process->redirec->fd = -1;
			}
			process->redirec = process->redirec->next;
		}
		process->redirec = process->redirec_head;
		process = process->next;
	}
}
