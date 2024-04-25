#include "../../minishell.h"

static void	exec_cmd(t_utils *utils, t_parse *current_process)
{
	char	*path;

	path = get_cmd_path(utils);
	if (!path)
		path = utils->path[0];
	if (execve(path, current_process->cmd, utils->env) == -1)
	{
		ft_putstr_fd(current_process->cmd[0], 2);
		ft_putendl_fd(" :command not found", 2);
		close_fds(utils->process, utils);
		free_utils(utils);
		exit(EXIT_FAILURE);
	}
}

static int	get_last_infile(t_parse *process)
{
	int	last_infile_fd;

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

static void	open_infiles(t_utils *utils, t_parse *process)
{
	process->redirec = process->redirec_head;
	while (process->redirec)
	{
		if (process->redirec->redir_type == MINUS)
		{
			process->redirec->fd = open(utils->process->redirec->doc, O_RDONLY);
			if (process->redirec->fd == -1)
				exit_process(utils);
		}
		process->redirec = process->redirec->next;
	}
}

void	execute_first_process(t_utils *utils, t_parse *process)
{
	int		in_redir_count;
	int		last_infile_fd;

	if (process->redirec_head)
	{
		open_infiles(utils, utils->process);
		last_infile_fd = get_last_infile(utils->process);
		if (dup2(last_infile_fd, STDIN_FILENO) == -1)
			exit_process(utils);
		close_fds(utils->process, utils); //OJO! ESTAMOS CERRANDO HEREDOCS DE MÁS
	}
	if (process->cmd && process->cmd[0]) //Cuando llegue el parseo bueno es posible que toque cambiarlo
		exec_cmd(utils, process);
	else
	{
		close_fds(process, utils);
		free_utils(utils);
		exit(FUNC_SUCCESS);
	}
}
