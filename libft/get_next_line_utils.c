/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmoran-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:39:08 by fmoran-m          #+#    #+#             */
/*   Updated: 2023/10/31 20:03:02 by fmoran-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_file(char **file)
{
	free (*file);
	*file = NULL;
	return (NULL);
}

size_t	ft_strlen_gnl(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*ptr;
	size_t	i;
	size_t	k;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	k = 0;
	ptr = (char *)ft_calloc((ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1), sizeof(char));
	if (!ptr)
		return (NULL);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[k])
	{
		ptr[i] = s2[k];
		i++;
		k++;
	}
	return (ptr);
}

char	*ft_strdup_gnl(char *s1)
{
	size_t	len;
	size_t	i;
	char	*ptr;

	if (!s1)
		return (NULL);
	len = ft_strlen_gnl(s1);
	ptr = (char *)malloc(len * (sizeof(char)) + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
