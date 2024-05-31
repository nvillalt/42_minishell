#include "../../minishell.h"

int error_message(t_utils *utils)
{
	if (utils->env)
		free_matrix(utils->env);
	if (utils->path)
		free_matrix(utils->path);
  printf("Error\n");
//  rl_clear_history();
  return (0);
}