#include "../../minishell.h"
static void	execute_here_doc(char *limiter)
{
	int		fd;
	char	*buffer;
	int		limiter_len;
	int		buffer_len;

	buffer = NULL;
	buffer_len = 0;
	limiter_len = ft_strlen(limiter);
	fd = open(".here_doc.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		exit (1) //Al loro con las liberaciones
	while (ft_strncmp(buffer, limiter, limiter_len)
		|| limiter_len + 1 != buffer_len)
	{
		if (buffer)
			free(buffer);
		ft_printf("> ");
		buffer = get_next_line(0);
		buffer_len = ft_strlen(buffer);
		if ((ft_strncmp(buffer, limiter, limiter_len)
				|| limiter_len + 1 != buffer_len))
			write(fd, buffer, buffer_len);
	}
	free(buffer);
	close(fd);
}

static void	check_here_doc(t_redir *redirec)
{
	while(redirec)
	{
		if (redirec->redir_type == HERE_DOC)
			execute_here_doc(redirec->doc);
		redirec = redirec->next;
	}
}

int	executor(t_parse *cmd_list)
{
	while(cmd_list)
	{
		check_here_doc(cmd_list->redirec);
		cmd_list = cmd_list->next;
	}
}