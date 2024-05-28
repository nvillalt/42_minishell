#include "../../minishell.h"

int	is_export_format(char *cmd)
{
	int	i;

	i = 0;
	if (!ft_isalpha(cmd[i]) && cmd[i] != '_')
		return (0);
	i++;
	while (cmd[i] && cmd[i] != '=' && ft_isalnum(cmd[i]))
		i++;
	if (cmd[i] == 0 || cmd[i] == '=')
		return (1);
	else
		return (0);
}