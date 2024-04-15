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

void	exit_with_number(char *cmd)
{
	int status;

	if (!check_number_cmd(cmd))
	{
		printf("exit\n");
		ft_putendl_fd("Numeric argument required", 2);
		exit(2);
	}
	status = ft_atoi(cmd);
	printf("exit\n");
	exit(status); //Tocará liberar todo lo que tenga hasta el momento, al loro
}

void	ft_exit(char **cmd)
{
	unsigned char	status;
	int				num;

	status = 0;
	num = count_cmds(cmd);
	if (num == 1)
	{
		printf("exit\n");
		exit(status); //Tocará liberar todo lo que tenga hasta el momento, al loro
	}
	else if (num == 2)
		exit_with_number(cmd[1]);
	else
	{
		printf("exit\n"); //Tocará liberar todo lo que tenga hasta el momento, al loro
		ft_putendl_fd("Too many arguments", 2);
		exit (1);
	}
}