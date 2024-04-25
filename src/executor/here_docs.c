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

static int	open_here_doc(t_redir *redirec, int temp_num)
{
	char	*str_num;

	str_num = ft_itoa(temp_num);
	if (!str_num)
		return(FUNC_FAILURE);
	redirec->heredoc_file = ft_strjoin("/tmp/.temp", str_num);
	free(str_num);
	if (!redirec->heredoc_file)
		return (FUNC_FAILURE);
	redirec->fd = open(redirec->heredoc_file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (redirec->fd == -1)
		return (FUNC_FAILURE);
	return (FUNC_SUCCESS);
}

static void	write_here_doc(t_parse *process)
{	
	char	*buffer;
	int		limiter_len;
	int		buffer_len;

	buffer = NULL;
	buffer_len = 0;
	limiter_len = ft_strlen(process->redirec->doc);
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
}



static int	exec_here_doc(t_utils *utils, t_parse *process, int temp_num)
{
	if(!open_here_doc(process->redirec ,temp_num))
	{
		utils->status = 1;
		return(FUNC_FAILURE);
	}
	write_here_doc(process);
	utils->status = 0;
	return (FUNC_SUCCESS);
}

int	open_multiple_heredocs(t_utils *utils, t_parse *process)
{
	int	temp_num;

	temp_num = 1;
	while(process)
	{
		while(process->redirec)
		{
			if (process->redirec->redir_type == HEREDOC)
			{
				if (!exec_here_doc(utils, process, temp_num))
					return (FUNC_FAILURE);
				temp_num++;
			}
			process->redirec = process->redirec->next;
		}
		process = process->next;
	}
	return (FUNC_SUCCESS);
}
