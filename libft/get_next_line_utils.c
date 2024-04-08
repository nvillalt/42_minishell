/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:36:41 by nvillalt          #+#    #+#             */
/*   Updated: 2024/03/08 15:59:46 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc_gnl(size_t count, size_t size)
{
	char	*temp;
	size_t	i;

	i = 0;
	temp = malloc(count * size);
	if (!temp)
		return (NULL);
	while (i < (count * size))
	{
		temp[i] = 0;
		i++;
	}
	return (temp);
}

size_t	ft_strlen_gnl(char *str)
{
	int	count;

	count = 0;
	if (str == 0)
		return (0);
	while (str[count] != '\0')
		count++;
	return (count);
}

int	ft_check_char(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strdup_gnl(char *src)
{
	char	*s;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen_gnl(src);
	s = ft_calloc_gnl(sizeof(char), len + 1);
	if (!s)
		return (0);
	while (src[i] != '\0')
	{
		s[i] = src[i];
		i++;
	}
	return (s);
}

char	*ft_strjoin_gnl(char *saved, char *buffer)
{
	char	*join;
	int		i;
	int		j;

	i = 0;
	j = 0;
	join = ft_calloc_gnl(sizeof(char), ft_strlen_gnl(saved) + ft_strlen_gnl(buffer) + 1);
	if (!join)
		return (free(saved), NULL);
	while (saved && saved[i] != '\0')
	{
		join[i] = saved[i];
		i++;
	}
	while (buffer[j] != '\0')
	{
		join[i] = buffer[j];
		i++;
		j++;
	}
	free(saved);
	return (join);
}
