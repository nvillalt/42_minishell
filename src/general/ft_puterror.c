#include "../../minishell.h"

int    ft_puterror(char *cmd)
{
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    perror(cmd);
    return (FUNC_FAILURE);
}

char	*free_puterror(char *str, char *str2, t_utils *utils, int status)
{
    if (str)
        free(str);
    if (str2)
        free(str2);
    if (utils)
        utils->status = status;
    perror("minishell");
    return (FUNC_FAILURE);
}