#include "../../minishell.h"

void	free_to_prompt(t_utils *utils)
{
	perror(NULL);
	close_all_pipes(utils);
	close_fds(utils->process, utils);
	free_lists(utils);
}
void	exit_process(t_utils *utils)
{
	perror(NULL);
	close_all_pipes(utils);
	close_fds(utils->process, utils);
	free_utils(utils);
	exit(EXIT_FAILURE);
}
void	exit_process_noerror(t_utils *utils)
{
	perror(NULL);
	close_all_pipes(utils);
	close_fds(utils->process, utils);
	free_utils(utils);
	exit(EXIT_SUCCESS);
}