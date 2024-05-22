#include "../../minishell.h"

static char	*create_new_buffer(char *buffer, char *val, char *key, int *i) // ES ESTA LA PEOR FUNCIÓN QUE HE ESCRITO NUNCA?????
{
	int		key_len;
	int		val_len;
	int		bef_exp_len;
	int		aft_exp_len;
	int		j;
	char	*new_buffer;
	char	*bef_exp;
	char	*after_exp;
	char	*temp;

	val_len = 0;
	if (val)
		val_len = ft_strlen(val);
	bef_exp_len = *i;
	key_len = ft_strlen(key);
	aft_exp_len = ft_strlen(buffer) - (bef_exp_len + key_len + 1);
	bef_exp = ft_substr(buffer, 0, bef_exp_len);
	if (!bef_exp)
	{
		perror("minishell");
		free(buffer);
		return (NULL);
	}
	if (aft_exp_len > 0)
	{
		after_exp = ft_substr(buffer, bef_exp_len + key_len + 1, aft_exp_len);
		if (!after_exp)
		{
			free(bef_exp);
			free(buffer);
			perror("minishell");
			return(NULL);
		}
	}
	if (!val)
	{
		new_buffer = ft_strjoin(bef_exp, after_exp);
		free(buffer);
		if (!new_buffer)
		{
			perror("minishell");
			return (NULL);
		}
		return (new_buffer);
	}
	temp = ft_strjoin(bef_exp, val);
	free(bef_exp);
	free(val);
	if (!temp)
	{
		free(buffer);
		free(after_exp);
		perror("minishell");
		return (NULL);
	}
	new_buffer = ft_strjoin(temp, after_exp);
	free(buffer);
	free(after_exp);
	if (!new_buffer)
	{
		perror("minishell");
		return (NULL);
	}
	*i += val_len; //CUIDADO QUE A LO MEJOR NOS SALTAMOS UNO
	return (new_buffer);
}

char	*get_keyhd(char *buffer, int i) //OJO CON SEGFAULT SI LE PASAMOS UN \0
{
	int		start;
	char	*key;

	start = i + 1;
	while (buffer[i] && buffer[i] != '\'' && buffer[i] != '\"' && buffer[i] != ' ')
		i++;
	if (start >= i)
		return (ft_strdup("$"));
	key = ft_substr(buffer, start, i - start);
	if (!key)
		return (NULL);
	return (key);
}

static char	*expand_heredoc(char *buffer, char **env)
{
	int		i;
	int		val_flag;
	char	*val;
	char	*key;

	i = 0;
	while (buffer[i])
	{
		val_flag = 1;
		if (buffer[i] == '$')
		{
			key = get_keyhd(buffer, i);
			if (!key)
				return (NULL);
			val = ft_getenv(env, key);
			if (!val)
				val_flag = 0;
			if (val_flag)
			{
				val = ft_strdup(val);
				if (!val)
				{
					free(key);
					perror("minishell");
					return (NULL);
				}
			}
			buffer = create_new_buffer(buffer, val, key, &i); //CUIDADO QUE A LO MEJOR NOS SALTAMOS 1
			if (!buffer)
			{
				free(key);
				if (val_flag)
					free(val);
				return (NULL);
			}
		}
		i++; //CUIDADO QUE A LO MEJOR NOS SALTAMOS UNO
	}
	return (buffer);
}

static char	*join_str(char *join, char const *s1, char const *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		join[i] = s2[j];
		j++;
		i++;
	}
	//join[i] = '\0';
	return (join);
}

static char	*ft_strjoin_hd(char const *s1, char const *s2)
{
	size_t	len;
	char	*join;

	if (*s1 == '\0' && *s2 == '\0')
		return (ft_strdup(""));
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	join = (char *)malloc(sizeof(char) * len);
	if (!join)
		return (0);
	join = join_str(join, s1, s2);
	return (join);
}

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

static int	get_file_name(t_redir *redirec, int temp_num)
{
	char	*str_num;

	str_num = ft_itoa(temp_num);
	if (!str_num)
	{
		perror("minishell");
		return(FUNC_FAILURE);
	}
	redirec->heredoc_file = ft_strjoin("/tmp/.temp", str_num);
	free(str_num);
	if (!redirec->heredoc_file)
	{
		perror("minishell");
		return (FUNC_FAILURE);
	}
	return(FUNC_SUCCESS);
}

static int	open_here_doc(t_redir *redirec, int *temp_num)
{
	if (!get_file_name(redirec, *temp_num))
		return (FUNC_FAILURE);
	while(access(redirec->heredoc_file, F_OK) == 0)
	{
		++*temp_num;
		free(redirec->heredoc_file);
		if (!get_file_name(redirec, *temp_num))
			return (FUNC_FAILURE);
	}
	redirec->fd = open(redirec->heredoc_file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (redirec->fd == -1)
		return (ft_puterror(redirec->doc));
	return (FUNC_SUCCESS);
}

static int	write_here_doc(t_parse *process, t_utils *utils)
{	
	char	*buffer;
	char	*temp;
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
		if (!buffer) //AL LORO CON ESTO, EL ORDEN DE EJECUCIÓN Y LIBERACIONES
		{
			close_fds(process, utils);
			ft_putendl_fd("minishell: warning: here-document delimited by end-of-file (wanted `eof')", STDERR_FILENO);
			utils->status = 0;
			return(1);
		}
		if (g_sigint != 0)
		{
			free(buffer);
			utils->status = 130;
			return (0);
		}
		if (process->redirec->heredoc_flag == EXPAND)
		{
			buffer = expand_heredoc(buffer, utils->env);
			if (!buffer)
				return (0);
		}
		buffer_len = ft_strlen(buffer);
		temp = ft_strjoin_hd(buffer, "\n");
		if (!temp)
		{
			free(buffer);
			utils->status = 1;
			perror("minishell");
			return (0); //PERROR Y DEMAS AL CAMBIAR LA FUNCION
		}
		free(buffer);
		buffer = temp;
		if (ft_strncmp_heredoc(buffer, process->redirec->doc, limiter_len)
			|| limiter_len != buffer_len)
			write(process->redirec->fd, buffer, buffer_len + 1);
	}
	free(buffer);
	return (1);
}

static int	exec_here_doc(t_utils *utils, t_parse *process, int *temp_num)
{
	if(!open_here_doc(process->redirec, temp_num))
	{
		utils->status = 1;
		return(FUNC_FAILURE);
	}
	if (!write_here_doc(process, utils))
		return (FUNC_FAILURE);
	utils->status = 0;
	return (FUNC_SUCCESS);
}

int	create_multiple_heredocs(t_utils *utils, t_parse *process)
{
	int	temp_num;

	temp_num = 1;
	heredoc_signals();
	rl_catch_signals = 0;
	while(process)
	{
		while(process->redirec)
		{
			if (process->redirec->redir_type == HEREDOC)
			{
				if (!exec_here_doc(utils, process, &temp_num))
				{
					rl_catch_signals = 1;
					return (FUNC_FAILURE);
				}
				temp_num++;
			}
			process->redirec = process->redirec->next;
		}
		process = process->next;
	}
	close_fds(process, utils);
	rl_catch_signals = 1;
	set_signals();
	return (FUNC_SUCCESS);
}
