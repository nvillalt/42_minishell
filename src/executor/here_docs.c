#include "../../minishell.h"

static int	ft_strncmp_heredoc(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (s1 == NULL && s2 == NULL)
		return (0);
	if (s1 == NULL)
		return (s2[i]);
	if (s2 == NULL)
		return (s1[i]);
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

static void	open_here_doc(t_utils *utils, t_parse *process, int temp_num)
{
	char	*buffer;
	int		limiter_len;
	int		buffer_len;

	process->redirec->heredoc_file = ft_strjoin(".temp", ft_itoa(temp_num));
	if (!process->redirec->heredoc_file)
	{
		free_utils(utils);
		close_fds(utils->process, utils);
		perror(NULL);
		exit(1); //LIBERAR TODO 
	}
	buffer = NULL;
	buffer_len = 0;
	limiter_len = ft_strlen(process->redirec->doc);
	process->redirec->fd = open(process->redirec->heredoc_file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (process->redirec->fd == -1)
	{
		free_lists(utils);
		close_fds(utils->process, utils);
		perror(NULL); //Liberar absolutamente todo
		utils->status = 1;
		return;
	}
	while (ft_strncmp_heredoc(buffer, process->redirec->doc, limiter_len)
			|| limiter_len != buffer_len)
	{
		if (buffer)
			free(buffer);
		buffer = readline("> ");
		buffer_len = ft_strlen(buffer);
		if (ft_strncmp_heredoc(buffer, process->redirec->doc, limiter_len)
			|| limiter_len != buffer_len)
			write(process->redirec->fd, buffer, buffer_len + 1);
	}
	free(buffer);
	utils->status = 0;
}

void	open_multiple_heredocs(t_utils *utils, t_parse *process)
{
	int	temp_num;

	temp_num = 1;
	while(process)
	{
		while(process->redirec)
		{
			if (process->redirec->redir_type == HEREDOC)
			{
				open_here_doc(utils, process, temp_num);
				if (utils->status != 0)
					return ;
				temp_num++;
			}
			process->redirec = process->redirec->next;
		}
		process = process->next;
	}
}
