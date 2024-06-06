/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_buffer_heredoc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:11:34 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/06 17:23:01 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*get_bef_exp_str(char *buffer, int i)
{
	int		bef_exp_len;
	char	*bef_exp;

	bef_exp_len = i;
	bef_exp = ft_substr(buffer, 0, bef_exp_len);
	if (!bef_exp)
		return (free_puterror(buffer, NULL, NULL, 1));
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
	while (buffer[i] && buffer[i] == '$')
	{
		i++;
		dollar_len++;
	}
	bef_exp_len = ft_strlen(bef_exp);
	key_len = ft_strlen(key);
	aft_exp_len = ft_strlen(buffer) - (bef_exp_len + key_len + 1);
	after_exp = ft_substr (buffer,
			bef_exp_len + key_len + dollar_len, aft_exp_len);
	if (!after_exp)
		return (free_puterror(buffer, NULL, NULL, 1));
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
			return (free_puterror(NULL, NULL, NULL, 1));
		return (new_buffer);
	}
	temp = ft_strjoin_hd(bef_exp, val);
	if (!temp)
		return (free_puterror(NULL, NULL, NULL, 1));
	new_buffer = ft_strjoin_hd(temp, after_exp);
	free (temp);
	if (!new_buffer)
		return (free_puterror(NULL, NULL, NULL, 1));
	return (new_buffer);
}

char	*create_new_buffer(char *buffer, char *val, char *key, int *i)
{
	char	*new_buffer;
	char	*bef_exp;
	char	*after_exp;

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
