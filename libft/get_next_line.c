/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvillalt <nvillalt@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:10:25 by nvillalt          #+#    #+#             */
/*   Updated: 2023/12/26 19:13:20 by nvillalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free_saved(char *saved)
{
	char	*aux;
	int		len;

	len = 0;
	while (saved[len] != '\0' && saved[len] != '\n')
		len++;
	if (saved[len] == '\n')
		len++;
	aux = ft_strdup_gnl(saved + len);
	free(saved);
	if (!aux)
		return (NULL);
	return (aux);
}

char	*ft_get_returned_line(char *saved)
{
	char	*final;
	int		len;

	len = 0;
	if (!saved || saved[len] == '\0')
		return (NULL);
	while (saved[len] != '\0' && saved[len] != '\n')
		len++;
	if (saved[len] ==  '\n')
		len++;
	final = ft_calloc_gnl(sizeof(char), len + 1); 	
	if (!final)
		return (NULL);
	len = 0;
	while (saved[len] != '\n' && saved[len] != '\0')
	{
		final[len] = saved[len];
		len++;
	}
	if (saved[len] == '\n')
		final[len] = saved[len];
	return (final);
}

char	*ft_read_fd(int fd, char *saved)
{
	char	*buffer; 
	ssize_t	read_chars;

	buffer = ft_calloc_gnl(sizeof(char), BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	read_chars = 1;
	while (read_chars > 0 && !ft_check_char(buffer, '\n'))
	{
		read_chars = read(fd, buffer, BUFFER_SIZE);
		if (read_chars == -1)
		{
			free(buffer);
			free(saved);
			saved = 0;
			return (NULL);
		}
		buffer[read_chars] = '\0';
		saved = ft_strjoin_gnl(saved, buffer);
	}
	free(buffer);
	return (saved);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char	*final;

	saved = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	saved = ft_read_fd(fd, saved);
	if (!saved)
		return (NULL);
	final = ft_get_returned_line(saved);
	if (!final)
	{
		if (saved)
		{
			free(saved);
			saved = 0;
			return (NULL);
		}
	}
	saved = ft_free_saved(saved);
	return (final);
}
