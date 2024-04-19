#include "../../minishell.h"

int	is_string_alpha(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && (ft_isalpha(cmd[i]) || cmd[i] == '=' || cmd[i] == '\"' || cmd[i] == '\''))
		i++;
	if (cmd[i] == 0)
		return (1);
	else
		return (0);
}