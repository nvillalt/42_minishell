#include "../../minishell.h"

void	exec_cmd(t_utils *utils, t_parse *current_process)
{
	char	*path;

	path = get_cmd_path(utils, current_process);
	//if (!path)
		//path = utils->path[0]; //NO es muy correcto. En caso de que no encuentre la ruta le paso una cualquiera. Documentarse
	if (execve(path, current_process->cmd, utils->env) == -1)
	{
		ft_putstr_fd(current_process->cmd[0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		close_fds(utils->process, utils);
		free_utils(utils);
		exit(127);
	}
}
