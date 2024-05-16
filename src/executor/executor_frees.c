#include "../../minishell.h"

void	free_to_prompt(t_utils *utils)
{
	unlink_files(utils->process);
	close_all_redirs(utils);
	close_fds(utils->process, utils);
	free_lists(utils);
}

void	exit_process(t_utils *utils)
{
	close_all_redirs(utils);
	close_fds(utils->process, utils);
	free_utils(utils);
	exit(EXIT_FAILURE);
}

void	exit_process_noerror(t_utils *utils)
{
	close_all_redirs(utils);
	close_fds(utils->process, utils);
	free_utils(utils);
	exit(EXIT_SUCCESS);
}

void	exit_process_custom(t_utils *utils, unsigned char status)
{
	close_all_redirs(utils);
	close_fds(utils->process, utils);
	free_utils(utils);
	exit(status);
}