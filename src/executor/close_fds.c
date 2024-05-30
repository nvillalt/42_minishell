#include "../../minishell.h"

void	unlink_files(t_parse *process)
{
	while (process)
	{
		process->redirec = process->redirec_head;
		while(process->redirec)
		{
			if (process->redirec->heredoc_file)
				unlink(process->redirec->heredoc_file);
			process->redirec = process->redirec->next;
		}
		process = process->next;
	}
}

void	close_redir_fd(int *pipe_fd)
{
	if (*pipe_fd != -1)
		close(*pipe_fd);
	*pipe_fd = -1;
}

void	close_all_redirs(t_utils *utils)
{
	close_redir_fd(&utils->main_pipe[0]);
	close_redir_fd(&utils->main_pipe[1]);
	close_redir_fd(&utils->aux_pipe[0]);
	close_redir_fd(&utils->aux_pipe[1]);
	close_redir_fd(&utils->saved_stdin);
	close_redir_fd(&utils->saved_stdout);
}

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
