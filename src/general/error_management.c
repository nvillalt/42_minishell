

#include "../../minishell.h"

int error_message(t_utils *utils)
{
  free_utils(utils);
  // if (utils->parse)
  //   clear_parse(utils->parse);
  rl_clear_history();
  printf("Error.\n");
  exit(EXIT_FAILURE); // Ver las salidas y los errores
  return (0);
}