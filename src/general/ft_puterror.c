#include "../../minishell.h"

int    ft_puterror(char *cmd)
{
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    perror(cmd);
    return (FUNC_FAILURE);
}