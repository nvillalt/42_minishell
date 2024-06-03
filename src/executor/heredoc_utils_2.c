/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <fmoran-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:32:24 by fmoran-m          #+#    #+#             */
/*   Updated: 2024/06/03 16:32:38 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*ft_strjoin_hd(char const *s1, char const *s2)
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

char	*append_newline(int *buffer_len, char *buffer, t_utils *utils)
{
	char	*temp;

	*buffer_len = ft_strlen(buffer);
	temp = ft_strjoin_hd(buffer, "\n");
	if (!temp)
		return (free_puterror(NULL, buffer, utils, 1));
	free(buffer);
	buffer = temp;
	return (buffer);
}

int	ft_strncmp_heredoc(const char *s1, const char *s2, size_t n)
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
