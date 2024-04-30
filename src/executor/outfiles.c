#include "../../minishell.h"

static int	open_outfiles(t_utils *utils, t_parse *process)
{
	int	last_outfile_fd;

	last_outfile_fd = -1;
	process->redirec = process->redirec_head;
	while (process->redirec)
	{
		if (process->redirec->redir_type == GREAT)
		{
			process->redirec->fd = open(process->redirec->doc, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			if (process->redirec->fd == -1)
				exit_process(utils);
			last_outfile_fd = process->redirec->fd;
		}
		if (process->redirec->redir_type == APPEND)
		{
			process->redirec->fd = open(process->redirec->doc, O_WRONLY | O_APPEND | O_CREAT, 0644);
			if (process->redirec->fd == -1)
				exit_process(utils);
			last_outfile_fd = process->redirec->fd;
		}
		process->redirec = process->redirec->next;
	}
	return (last_outfile_fd);
}

int	redirec_outfile(t_utils *utils, t_parse *process)
{
	int	last_outfile_fd;

	last_outfile_fd = open_outfiles(utils, process);
	if (last_outfile_fd == -1)
		return (FUNC_FAILURE);
	if (dup2(last_outfile_fd, STDOUT_FILENO) == -1)
		exit_process(utils);
	close_fds(utils->process, utils); 
	return (FUNC_SUCCESS);
}