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

int	ft_exit(char **cmd)
{
	unsigned char	status;
	int				num;

	status = 0;
	num = count_matrix(cmd);
	if (num == 1)
	{
		printf("exit\n");
		return (FUNC_SUCCESS); //Tocará liberar todo lo que tenga hasta el momento, al loro
	}
	else if (num == 2)
	{
		if (!check_number_cmd(cmd[1]))
		{
			printf("exit\n");
			ft_putendl_fd("Numeric argument required", 2);
			return (2);
		}
		status = ft_atoi(cmd[1]);
		printf("exit\n");
		return (status);
	}
	else
	{
		printf("exit\n"); //Tocará liberar todo lo que tenga hasta el momento, al loro
		ft_putendl_fd("Too many arguments", 2);
		return(1);
	}
}
