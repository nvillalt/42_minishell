#include "../../minishell.h"

static void	exec_cmd(t_utils *utils, t_parse *current_process)
{
	char	*path;

	path = get_cmd_path(utils);
	if (!path)
		path = utils->path[0]; //NO es muy correcto. En caso de que no encuentre la ruta le paso una cualquiera. Documentarse
	if (execve(path, current_process->cmd, utils->env) == -1)
	{
		ft_putstr_fd(current_process->cmd[0], STDERR_FILENO);
		ft_putendl_fd(" :command not found", STDERR_FILENO);
		close_fds(utils->process, utils);
		free_utils(utils);
		exit(EXIT_FAILURE);
	}
}

static int	get_last_infile(t_parse *process)
{
	int	last_infile_fd;

	last_infile_fd = -1;
	process->redirec = process->redirec_head;
	while(process->redirec)
	{
		if (process->redirec->redir_type == MINUS
			|| process->redirec->redir_type == HEREDOC)
			last_infile_fd = process->redirec->fd;
		process->redirec = process->redirec->next;
	}
	process->redirec = process->redirec_head;
	return(last_infile_fd);
}

static int	open_infiles(t_utils *utils, t_parse *process)
{
	int	last_infile_fd;

	last_infile_fd = -1;
	process->redirec = process->redirec_head;
	while (process->redirec)
	{
		if (process->redirec->redir_type == MINUS)
		{
			process->redirec->fd = open(utils->process->redirec->doc, O_RDONLY);
			if (process->redirec->fd == -1)
				exit_process(utils);
			last_infile_fd = process->redirec->fd;
		}
		if (process->redirec->redir_type == HEREDOC)
		{
			process->redirec->fd = open(utils->process->redirec->heredoc_file, O_RDONLY);
			if (process->redirec->fd == -1)
				exit_process(utils);
			last_infile_fd = process->redirec->fd;
		}
		process->redirec = process->redirec->next;
	}
	return (last_infile_fd);
}

static void	redirec_infile(t_utils *utils, t_parse *process)
{
	int	last_infile_fd;

	last_infile_fd = open_infiles(utils, process);
	if (last_infile_fd == -1)
		return ;
	if (dup2(last_infile_fd, STDIN_FILENO) == -1)
		exit_process(utils);
	close_fds(utils->process, utils); 
}

static int	open_outfiles(t_utils *utils, t_parse *process)
{
	int	last_outfile_fd;

	last_outfile_fd = -1;
	process->redirec = process->redirec_head;
	while (process->redirec)
	{
		if (process->redirec->redir_type == GREAT)
		{
			process->redirec->fd = open(utils->process->redirec->doc, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			if (process->redirec->fd == -1)
				exit_process(utils);
			last_outfile_fd = process->redirec->fd;
		}
		if (process->redirec->redir_type == APPEND)
		{
			process->redirec->fd = open(utils->process->redirec->doc, O_WRONLY | O_APPEND | O_CREAT, 0644);
			if (process->redirec->fd == -1)
				exit_process(utils);
			last_outfile_fd = process->redirec->fd;
		}
		process->redirec = process->redirec->next;
	}
	return (last_outfile_fd);
}

static int	redirec_outfile(t_utils *utils, t_parse *process)
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

void	execute_first_process(t_utils *utils, t_parse *process)
{
	int		in_redir_count;

	close_pipe_fd(utils->main_pipe[0]);
	redirec_infile(utils, process);
	if (!redirec_outfile(utils, process))
	{
		if (process->next)
		{
			if (dup2(utils->main_pipe[1], STDOUT_FILENO) == -1)
				exit_process(utils);
		}
	}
	close_pipe_fd(utils->main_pipe[1]);
	if (process->cmd && process->cmd[0]) //Cuando llegue el parseo bueno es posible que toque cambiarlo
		exec_cmd(utils, process);
	else
		exit_process_noerror(utils);
}
