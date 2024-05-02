#include "../../minishell.h"

static int	check_number_cmd(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] == '-' || cmd[i] == '+')
		i++;
	if (!cmd[i])
		return (0);
	while(ft_isdigit(cmd[i]))
		i++;
	if (!cmd[i])
		return (1);
	else
		return (0);
}

void	exit_with_number(t_utils *utils, char *cmd)
{
	int status;

	if (!check_number_cmd(cmd))
	{
		printf("exit\n");
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit_process_custom(utils, 2);
	}
	status = ft_atoi(cmd);
	printf("exit\n");
	exit_process_custom(utils, status); //Tocará liberar todo lo que tenga hasta el momento, al loro
}

void	ft_exit(char **cmd, t_utils *utils)
{
	unsigned char	status;
	int				num;

	status = 0;
	num = count_matrix(cmd);
	if (num == 1)
	{
		printf("exit\n");
		exit_process_custom(utils, status); //Tocará liberar todo lo que tenga hasta el momento, al loro
	}
	else if (num == 2)
		exit_with_number(utils, cmd[1]);
	else
	{
		printf("exit\n"); //Tocará liberar todo lo que tenga hasta el momento, al loro
		ft_putendl_fd("minishell: exit: No such file or directory", 2);
		exit_process_custom(utils, 127);
	}
}