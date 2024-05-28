#include "../../minishell.h"

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
		*i += ft_strlen(val);
	return (new_buffer);
}

static int	write_here_doc(t_parse *process, t_utils *utils)
{	
	char	*buffer;
	int		limiter_len;
	int		buffer_len;

	init_values_hd(&buffer, &limiter_len, &buffer_len, process);
	while (ft_strncmp_heredoc(buffer, process->redirec->doc, limiter_len)
			|| limiter_len != buffer_len)
	{
		buffer = init_buffer(buffer);
		if (!buffer)
			return (control_eof_hd(process, utils));
		if (g_sigint != 0)
			return (control_sigint_hd(buffer, utils));
		buffer = check_expansor_hd(process, buffer, utils);
		if (!buffer)
			return (0);
		buffer = append_newline(&buffer_len, buffer, utils);
		if (!buffer)
			return (FUNC_FAILURE);
		if (ft_strncmp_heredoc(buffer, process->redirec->doc, limiter_len)
			|| limiter_len != buffer_len)
			write(process->redirec->fd, buffer, buffer_len + 1);
	}
	return (free(buffer), FUNC_SUCCESS);
}

static int	exec_heredoc(t_utils *utils, t_parse *process, int *temp_num)
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

static int	create_heredoc_loop(t_parse *process, t_utils *utils)
{
	int	temp_num;

	temp_num = 1;
	while(process)
	{
		while(process->redirec)
		{
			if (process->redirec->redir_type == HEREDOC)
			{
				if (!exec_heredoc(utils, process, &temp_num))
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
	return (FUNC_SUCCESS);
}

int	create_multiple_heredocs(t_utils *utils, t_parse *process)
{
	heredoc_signals();
	rl_catch_signals = 0;
	if (!create_heredoc_loop(process, utils))
		return (FUNC_FAILURE);
	close_fds(process, utils);
	rl_catch_signals = 1;
	set_signals();
	return (FUNC_SUCCESS);
}
