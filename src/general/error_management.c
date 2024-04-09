#include "../../minishell.h"

int error_message(t_utils *utils)
{
  if (utils->env)
    free_matrix(utils->env);
  exit(EXIT_FAILURE);
  return (0);
}