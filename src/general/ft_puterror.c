#include "../../minishell.h"

int	ft_puterror(char *cmd)
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
	return (NULL);
}

void	free_ptrs(void *ptr1, void *ptr2)
{
	if (ptr1)
		free(ptr1);
	if (ptr2)
		free(ptr2);
}

char	*updt_status_return(t_utils *utils, int status)
{
	utils->status = status;
	return (NULL);
}

int	free_puterror_int(char *str, char *str2, t_utils *utils, int status)
{
	if (str)
		free(str);
	if (str2)
		free(str2);
	if (utils)
		utils->status = status;
	perror("minishell");
	return (0);
}
