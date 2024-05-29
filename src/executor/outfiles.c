#include "../../minishell.h"

static int	open_great(int last_outfile_fd, t_utils *utils, t_parse *process)
{
	process->redirec->fd = open(process->redirec->doc, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (process->redirec->fd == -1)
	{
		ft_puterror(process->redirec->doc);
		if (utils->parent_builtin == 1) //CUIDADO CON QUE NO SEA -1
			return (-2);
		else
			exit_process(utils);
	}
	last_outfile_fd = process->redirec->fd;
	return (last_outfile_fd);
}

static int	open_append(int last_outfile_fd, t_utils *utils, t_parse *process)
{
	process->redirec->fd = open(process->redirec->doc, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (process->redirec->fd == -1)
	{
		ft_puterror(process->redirec->doc);
		if (utils->parent_builtin == 1)
			return (FUNC_FAILURE);
		else
			exit_process(utils);
	}
	last_outfile_fd = process->redirec->fd;
	return (last_outfile_fd);
}

static int	open_outfiles(t_utils *utils, t_parse *process)
{
	int	last_outfile_fd;

	last_outfile_fd = -1;
	process->redirec = process->redirec_head;
	while (process->redirec)
	{
		if (process->redirec->redir_type == GREAT)
			last_outfile_fd = open_great(last_outfile_fd, utils, process);
		if (process->redirec->redir_type == APPEND)
			last_outfile_fd = open_append(last_outfile_fd, utils, process);
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
	if (last_outfile_fd == -2)
		return (-2);
	if (dup2(last_outfile_fd, STDOUT_FILENO) == -1)
	{
		perror("minishell");
		if (utils->parent_builtin == 1)
			return (-2);
		else
			exit_process(utils);
	}
	close_fds(utils->process, utils); 
	return (FUNC_SUCCESS);
}
