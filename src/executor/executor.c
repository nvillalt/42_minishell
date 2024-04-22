#include "../../minishell.h"

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

//	open_multiple_heredocs(utils->process);
	process_list_len = process_counter(utils->process);
	process_index = 1;
	if (process_index == 1)
	{
		pid = fork();
		if (pid == 0)
			execute_first_process(utils, main_pipe);
		wait(&status);
	}
	/*
	else if (process_index < process_list_len)
		execute_mid_process(utils, main_pipe, aux_pipe);
	else if (process_index == process_list_len)
		execute_last_process(utils, main_pipe);
	*/
	return (0);
}
