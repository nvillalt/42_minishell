#include "../../minishell.h"

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
	return (join);
}

static char	*ft_strjoin_hd(char const *s1, char const *s2)
{
	size_t	len;
	char	*join;

	if (*s1 == '\0' && *s2 == '\0')
		return (ft_strdup(""));
	else if (!*s1)
	{
		join = ft_strdup(s2);
		if (!join)
			return (NULL);
		return (join);
	}
	else if (!*s2)
	{
		join = ft_strdup(s1);
		if (!join)
			return (NULL);
		return (join);
	}
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	join = (char *)ft_calloc(sizeof(char), len);
	if (!join)
		return (NULL);
	join = join_str(join, s1, s2);
	return (join);
}

static char	*get_bef_exp_str(char *buffer, int i)
{
	int		bef_exp_len;
	char	*bef_exp;

	bef_exp_len = i;
	bef_exp = ft_substr(buffer, 0, bef_exp_len);
	if (!bef_exp)
	{
		free(buffer);
		perror("minishell");
		return (NULL);
	}
	return (bef_exp);
}

static char	*get_aft_exp_str(char *buffer, int i, char *key, char *bef_exp)
{
	int		aft_exp_len;
	int		bef_exp_len;
	int		key_len;
	int		dollar_len;
	char	*after_exp;

	dollar_len = 0;
	while(buffer[i] && buffer[i] == '$')
	{
		i++;
		dollar_len++;
	}
	bef_exp_len = ft_strlen(bef_exp);
	key_len = ft_strlen(key);
	aft_exp_len = ft_strlen(buffer) - (bef_exp_len + key_len + 1);
	after_exp = ft_substr(buffer, bef_exp_len + key_len + dollar_len, aft_exp_len);
	if (!after_exp)
	{
		free(buffer);
		perror("minishell");
		return (NULL);
	}
	return (after_exp);
}

static char	*get_new_buffer(char *val, char *bef_exp, char *after_exp)
{
	char	*new_buffer;
	char	*temp;

	if (!val)
	{
		new_buffer = ft_strjoin_hd(bef_exp, after_exp);
		if (!new_buffer)
		{
			perror("minishell");
			return (NULL);
		}
		return (new_buffer);
	}
	temp = ft_strjoin_hd(bef_exp, val);
	if (!temp)
	{
		perror("minishell");
		return (NULL);
	}
	new_buffer = ft_strjoin_hd(temp, after_exp);
	free(temp);
	if (!new_buffer)
	{
		perror("minishell");
		return (NULL);
	}
	return (new_buffer);
}

static char	*create_new_buffer(char *buffer, char *val, char *key, int *i) // ES ESTA LA PEOR FUNCIÓN QUE HE ESCRITO NUNCA?????
{
	char	*new_buffer;
	char	*bef_exp;
	char	*after_exp;
	char	*temp;

	bef_exp = get_bef_exp_str(buffer, *i);
	if (!bef_exp)
		return (NULL);
	after_exp = get_aft_exp_str(buffer, *i, key, bef_exp);
	if (!after_exp)
	{
		if (bef_exp)
			free(bef_exp);
		return (NULL);
	}
	new_buffer = get_new_buffer(val, bef_exp, after_exp);
	free(buffer);
	if (bef_exp)
		free(bef_exp);
	free(after_exp);
	if (!new_buffer)
		return (NULL);
	if (val)
		*i += ft_strlen(val); //CUIDADO QUE A LO MEJOR NOS SALTAMOS UNO
	return (new_buffer);
}

char	*get_keyhd(char *buffer, int i)
{
	int		start;
	char	*key;

	while(buffer[i] && buffer[i] == '$')
		i++;
	i--;
	start = i + 1;
	i++;
	while (buffer[i] && ft_isalnum(buffer[i]))
		i++;
	if (start == i)
		return (ft_strdup("$"));
	key = ft_substr(buffer, start, i - start);
	if (!key)
		return (NULL);
	return (key);
}

static char	*expand_heredoc(char *buffer, char **env)
{
	int		i;
	int		j;
	char	*val;
	char	*key;

	i = 0;
	while (buffer[i])
	{
		j = i;
		if (buffer[i] == '$')
		{
			key = get_keyhd(buffer, i);
			if (!key)
				return (NULL);
			if (*key  == '$')
			{
				val = ft_strdup(key);
				if (!val)
				{
					free(key);
					perror("minishell");
					return (NULL);
				}
			}
			else
			{
				val = ft_getenv(env, key);
				if (val)
				{
					val = ft_strdup(val); //LEAK
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
					if (val)
						free(val);
					return (NULL);
				}
			}
			if (key)
				free(key);
			if (val)
				free(val);
		}
		if (i == j)
			i++; //CUIDADO QUE A LO MEJOR NOS SALTAMOS UNO
	}
	return (buffer);
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
