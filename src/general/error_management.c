

#include "../../minishell.h"

int error_message(t_utils *utils)
{
  if (utils->env)
    free_matrix(utils->env); // ver si esto funciona sin problemas, ya que free_matrix devuelve una matriz
  if (utils->path)
    free_matrix(utils->path);
  printf("Error.\n");
  exit(EXIT_FAILURE); // Ver las salidas y los errores
  return (0);
}