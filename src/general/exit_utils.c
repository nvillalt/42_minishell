#include "../../minishell.h"

void	exit_matrix_str(char *str, char **matrix, char *error_str, t_utils *utils)
{
	if (str)
		free(str);
	if (matrix)
		free(matrix);
	perror(error_str);
	exit_process(utils);
}

void	exit_process_path(t_utils *utils, t_parse *process)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(process->cmd[0]);
	exit_process_custom(utils, 127);
}

int	change_status(t_utils *utils, int status)
{
	utils->status = 1;
	return (FUNC_FAILURE);
}