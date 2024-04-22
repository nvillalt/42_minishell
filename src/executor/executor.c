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

static void	open_here_doc(t_utils *utils, int temp_num)
{
	char	*name_temp;
	char	*buffer;
	int		limiter_len;
	int		buffer_len;

	name_temp = ft_strjoin(".temp", ft_itoa(temp_num));
	if (!name_temp)
		exit(1); //LIBERAR TODO 
	buffer = NULL;
	buffer_len = 0;
	limiter_len = ft_strlen(utils->process->redirec->doc);
	utils->process->redirec->fd = open(name_temp, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (utils->process->redirec->fd == -1)
	{
		perror(NULL); //Liberar absolutamente todo
		return;
	}
	while (ft_strncmp_heredoc(buffer, utils->process->redirec->doc, limiter_len)
			|| limiter_len != buffer_len)
	{
		if (buffer)
			free(buffer);
		write(STDERR_FILENO, "> ", 2);
		buffer = get_next_line(STDIN_FILENO);
		buffer_len = ft_strlen(buffer);
		if (ft_strncmp_heredoc(buffer, utils->process->redirec->doc, limiter_len)
			|| limiter_len != buffer_len)
			write(utils->process->redirec->fd, buffer, buffer_len + 1);
	}
	free(buffer);
}

static void	open_multiple_heredocs(t_utils *utils)
{
	int	temp_num;

	temp_num = 1;
	while(utils->process)
	{
		while(utils->process->redirec)
		{
			if (utils->process->redirec->redir_type == HEREDOC)
			{
				open_here_doc(utils, temp_num);
				temp_num++;
			}
			utils->process->redirec = utils->process->redirec->next;
		}
		utils->process = utils->process->next;
	}
}

static int	process_counter(t_parse *process)
{
	int	i;

	i = 0;
	while(process)
	{
		process = process->next;
		i++;
	}
	return (i);
}

static void	exec_cmd(t_utils *utils)
{
	char	*path;

	path = get_cmd_path(utils);
	if (execve(path, utils->process->cmd, utils->env) == -1)
		exit(1); //Perror,  free, close, exit
}

static void	execute_first_process(t_utils *utils, int *main_pipe)
{
	t_redir	*head;
	int		i;
	int		in_redir_count;
	int		*infile_fds;

	in_redir_count = 0;
	head = utils->process->redirec;
	while(utils->process->redirec)
	{
		if (utils->process->redirec->redir_type = MINUS)
			in_redir_count++;
		utils->process->redirec = utils->process->redirec->next;
	}
	utils->process->redirec = head;
	infile_fds = malloc(in_redir_count * sizeof(int));
	if (!infile_fds)
		exit(1); //LIBERAR ABSOLUTAMENTE TODO Y SALIR
	i = 0;
	while (utils->process->redirec)
	{
		if (utils->process->redirec->redir_type = MINUS)
		{
			infile_fds[i] = open(utils->process->redirec->doc, O_RDONLY);
			if (infile_fds[i] == -1)
				exit(1); //EN REALIDAD NO HAY QUE SALIR. PRINTEAMOS ERROR Y LIBERAMOS TODO
			i++;
		}
		utils->process->redirec = utils->process->redirec->next;
	}
	if (dup2(infile_fds[i - 1], STDIN_FILENO) == -1) //Nos aseguramos de ejecutar la redirección solo con el ultimo
		exit(1); //LIBERAR, PERROR, CERRAR Y SALIR
	i = 0;
	while(i < in_redir_count)
	{
		if(close(infile_fds[i]) == -1)
			exit(1); //LIBERAR, PERROR, CERRAR Y SALIR
		i++;
	}
	free(infile_fds);
	exec_cmd(utils);
}

int	executor(t_utils *utils)
{
	int	process_list_len;
	int	process_index;
	int	main_pipe[2];
	int	aux_pipe[2];
	int	status;
	pid_t pid;

	open_multiple_heredocs(utils);
	/*
	process_list_len = process_counter(utils->process);
	process_index = 1;
	if (process_index == 1)
	{
		pid = fork();
		if (pid == 0)
			execute_first_process(utils, main_pipe);
		wait(&status);
	}
	else if (process_index < process_list_len)
		execute_mid_process(utils, main_pipe, aux_pipe);
	else if (process_index == process_list_len)
		execute_last_process(utils, main_pipe);
*/	
	return (0);
}
