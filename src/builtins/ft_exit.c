#include "../../minishell.h"

static void	print_buexit_error(char *cmd, t_utils *utils)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	exit_process_custom(utils, 2);
}

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

	if (utils->process->next == NULL)
		printf("exit\n");
	if (!check_number_cmd(cmd))
		print_buexit_error(cmd, utils);
	status = ft_atoi(cmd);
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
		if (utils->process->next == NULL)
			printf("exit\n"); //Salida de errores o salida normal?
		exit_process_custom(utils, status); //Tocará liberar todo lo que tenga hasta el momento, al loro
	}
	else if (num == 2)
		exit_with_number(utils, cmd[1]);
	else
	{
		if (utils->process->next == NULL)
			printf("exit\n"); //Tocará liberar todo lo que tenga hasta el momento, al loro
		if (!check_number_cmd(cmd[1]))
			print_buexit_error(cmd[1], utils);
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		exit_process_custom(utils, 127);
	}
}