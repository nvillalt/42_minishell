#include "../../minishell.h"

int	control_eof_hd(t_parse *process, t_utils *utils)
{
	close_fds(process, utils);
	ft_putendl_fd("minishell: warning: here-document delimited by end-of-file (wanted `eof')", STDERR_FILENO);
	utils->status = 0;
	return(1);
}
int	control_sigint_hd(char *buffer, t_utils *utils)
{
	free(buffer);
	utils->status = 130;
	return (0);
}

void	init_values_hd(char **buffer, int *limiter_len, int *buffer_len, t_parse *process)
{
	*buffer = NULL;
	*buffer_len = 0;
	*limiter_len = ft_strlen(process->redirec->doc);
}

char	*init_buffer(char *buffer)
{
	if (buffer)
		free(buffer);
	buffer = readline("> ");
	return (buffer);
}
